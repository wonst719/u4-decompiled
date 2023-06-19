/* CDDA player: loosely based on information from https://www.shdon.com/dos/sound */
/*#define CDDA_TRACE*/
#ifdef CDDA_TRACE
#include <stdio.h>
#endif

#include <dos.h>

extern cdecl CdCheckMscdex();
extern int cdecl CdSendDriverRequest();
extern cdecl CdGetTimeMinuteSecond();

#ifdef WIN32

CdCheckMscdex()
{}

CdSendDriverRequest(a, b)
int a;
int b;
{}

CdGetTimeMinuteSecond()
{}

#endif

typedef unsigned char byte;
typedef unsigned int word;
typedef unsigned long dword;

/* Requires MSCDEX v2.10+ */

/* length = 13 */
typedef struct RequestHeader
{
	byte length; /* 00 */
	byte subunitCode; /* 01 */
	byte commandCode; /* 02 */
	word status; /* 03 */
	byte reserved[8];
} RequestHeader;

/* command code = 3 */
typedef struct IoctlInputReq
{
	RequestHeader requestHeader;
	byte mediaDescriptor; /* 0D */

	word transferAddressOff; /* 0E */
	word transferAddressSeg; /* 10 */
} IoctlInputReq;

/* ioctl code = 10, transfer length = 7 */
typedef struct AudioDiskInfo
{
	byte controlBlockCode; /* == 10 */
	byte lowestTrackNumber;
	byte highestTrackNumber;
	dword leadoutPosition;
} AudioDiskInfo;

/* ioctl code = 11, transfer length = 7 */
typedef struct AudioTrackInfo
{
	byte controlBlockCode; /* == 11 */
	byte trackNumber;
	dword startingPoint;
	byte trackControlInfo;
} AudioTrackInfo;

typedef struct PlayAudioReq
{
	RequestHeader requestHeader;
	byte addressingMode; /* 0D */
	dword startingSector; /* 0E */
	dword sectorsToRead; /* 12 */
} PlayAudioReq;

typedef struct StopAudioReq
{
	RequestHeader requestHeader;
} StopAudioReq;

/* trackLengthInSecond = hsg / 75 */
static byte currentPlayingTrack;
static byte loopTrack;
static word playStartTimeMinSec;
static dword playingTrackLengthHsg;

static AudioDiskInfo audioDiskInfo;

static dword RedbookToHsg(redBook)
dword redBook;
{
	register word minutes = redBook >> 16;
	register byte seconds = redBook >> 8;
	register byte frames = redBook;

	return (dword)(minutes * 60 + seconds) * 75 + frames;
}

#define MY_FP_OFF(fp)	((unsigned)(fp))
#define MY_FP_SEG(fp)	((unsigned)((unsigned long)(fp) >> 16))

#define FAR_PARAM(x) MY_FP_OFF(x), MY_FP_SEG(x)

#define CD_DRIVE_STATUS_FLAG_ERROR (1 << 15)
#define CD_DRIVE_STATUS_FLAG_BUSY (1 << 9)
#define CD_DRIVE_STATUS_FLAG_DONE (1 << 8)

extern byte cdromAvailable;

extern word numberOfDriveLetters;
extern word startingDriveLetter;

#ifdef WIN32

byte cdromAvailable;

word numberOfDriveLetters;
word startingDriveLetter;

#endif

my_zeromem(ptr, cnt)
void* ptr;
int cnt;
{
#if 1
	register byte* bp = (byte*)ptr;
	register int i;
	for (i = 0; i < cnt; i++)
	{
		*bp++ = 0;
	}
#else
	register word* wp = (word*)ptr;
	register int i;
	for (i = 0; i < cnt; i += sizeof(word))
	{
		*wp++ = 0;
	}
	if (i != cnt)
	{
		*(((byte*)wp) + 1) = 0;
	}
#endif
}

CdRequestAudioDiskInfo()
{
	IoctlInputReq ioctlRead;

	if (!cdromAvailable)
		return;

#ifdef CDDA_TRACE
	printf("CdromAvailable %u\n", cdromAvailable);
	printf("NumberOfDriveLetters %u\n", numberOfDriveLetters);
	printf("StartingDriveLetter %u\n", startingDriveLetter);
#endif

	my_zeromem(&audioDiskInfo, sizeof(audioDiskInfo));
	my_zeromem(&ioctlRead, sizeof(ioctlRead));

	ioctlRead.requestHeader.commandCode = 3;
	ioctlRead.requestHeader.length = 18; /* FIXME: dosbox doesn't seem to care */

	ioctlRead.transferAddressOff = MY_FP_OFF(&audioDiskInfo);
	ioctlRead.transferAddressSeg = MY_FP_SEG(&audioDiskInfo);

#ifdef CDDA_TRACE
	printf("ioctl ES:BX = %u:%u\n", ioctlRead.transferAddressOff, ioctlRead.transferAddressSeg);
#endif

	audioDiskInfo.controlBlockCode = 10;

	CdSendDriverRequest(FAR_PARAM(&ioctlRead));

#ifdef CDDA_TRACE
	printf("after ioctl len = %d\n", ioctlRead.requestHeader.length);
	printf("after ioctl ES:BX = %u:%u\n", ioctlRead.transferAddressOff, ioctlRead.transferAddressSeg);
#endif

	if (ioctlRead.requestHeader.status & CD_DRIVE_STATUS_FLAG_ERROR)
	{
		/* error */
	}

#ifdef CDDA_TRACE
	printf("Status %u\n", ioctlRead.requestHeader.status);

	printf("Low %u\n", audioDiskInfo.lowestTrackNumber);
	printf("High %u\n", audioDiskInfo.highestTrackNumber);
	printf("Leadout %lu\n", audioDiskInfo.leadoutPosition);
#endif
}

CdPlayAudio(track)
byte track;
{
	AudioTrackInfo trackInfo;
	IoctlInputReq ioctlRead;
	PlayAudioReq playAudio;

	dword startingSector;
	dword stopSector;
	dword sectorsToRead;

	if (!cdromAvailable)
		return;

	my_zeromem(&trackInfo, sizeof(trackInfo));
	my_zeromem(&ioctlRead, sizeof(ioctlRead));

	currentPlayingTrack = 0;
	loopTrack = 0;

	ioctlRead.requestHeader.commandCode = 3;
	ioctlRead.requestHeader.length = 18; /* FIXME: dosbox doesn't seem to care */

	ioctlRead.transferAddressOff = MY_FP_OFF(&trackInfo);
	ioctlRead.transferAddressSeg = MY_FP_SEG(&trackInfo);

	trackInfo.controlBlockCode = 11;
	trackInfo.trackNumber = track;

	CdSendDriverRequest(FAR_PARAM(&ioctlRead));

	if (ioctlRead.requestHeader.status & CD_DRIVE_STATUS_FLAG_ERROR)
	{
		/* error */
		return;
	}

	if (trackInfo.trackControlInfo & 0x40)
	{
		/* data track */
		return;
	}

	startingSector = trackInfo.startingPoint;

	if (track == audioDiskInfo.highestTrackNumber)
	{
		stopSector = audioDiskInfo.leadoutPosition;
	}
	else
	{
		trackInfo.trackNumber = track + 1;
		CdSendDriverRequest(FAR_PARAM(&ioctlRead));

		stopSector = trackInfo.startingPoint;
	}

	sectorsToRead = RedbookToHsg(stopSector) - RedbookToHsg(startingSector);

	playingTrackLengthHsg = sectorsToRead;

	my_zeromem(&playAudio, sizeof(playAudio));

	playAudio.requestHeader.commandCode = 132;
	playAudio.requestHeader.length = 21;

	/* just use hsg mode? */
	playAudio.addressingMode = 1;
	playAudio.startingSector = startingSector;
	playAudio.sectorsToRead = sectorsToRead;

	CdSendDriverRequest(FAR_PARAM(&playAudio));

	currentPlayingTrack = track;

	/*return playAudio.requestHeader.status;*/
}

CdStopAudio()
{
	StopAudioReq stopAudio;

	if (!cdromAvailable)
		return;

	currentPlayingTrack = 0;
	loopTrack = 0;

	stopAudio.requestHeader.commandCode = 133;
	stopAudio.requestHeader.length = 5;

	CdSendDriverRequest(FAR_PARAM(&stopAudio));

	/*return stopAudio.requestHeader.status;*/
}

CdPlayLoopAudio(track)
byte track;
{
	CdPlayAudio(track);
	loopTrack = 1;
	playStartTimeMinSec = CdGetTimeMinuteSecond();
}

/* required poll interval: 1 sec */
CdCallback()
{
	register word currentMinSec;
	register word trackLengthInSeconds;

	if (currentPlayingTrack != 0)
	{
		currentMinSec = CdGetTimeMinuteSecond();
		if (currentMinSec != playStartTimeMinSec)
		{
			if (currentMinSec < playStartTimeMinSec)
				currentMinSec += 3600;

			trackLengthInSeconds = (playingTrackLengthHsg + 74) / 75;

			if (currentMinSec - playStartTimeMinSec >= trackLengthInSeconds)
			{
				CdPlayLoopAudio(currentPlayingTrack);
			}
		}
	}
}
