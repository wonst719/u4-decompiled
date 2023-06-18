#ifndef __U4_CDDA_H__
#define __U4_CDDA_H__

extern cdecl CdCheckMscdex();
extern int cdecl CdSendDriverRequest(void*);
extern CdRequestAudioDiskInfo();
extern CdPlayAudio(unsigned char);
extern CdPlayLoopAudio(unsigned char);
extern CdStopAudio();

#endif
