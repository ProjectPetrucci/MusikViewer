//Copyright (C) 2018 Michail Montesatnos <musikviewer@imslp.org>
//=============================================================================
//  MuseScore
//  Music Composition & Notation
//
//  Copyright (C) 2002-2012 Werner Schweer
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2
//  as published by the Free Software Foundation and appearing in
//  the file LICENCE.GPL
//=============================================================================

#include "config.h"
#include "preferences.h"
#include "driver.h"
#include "qaudiodriver.h"

#ifdef USE_JACK
#include "jackaudio.h"
#endif


#ifdef USE_ALSA
#include "alsa.h"
#endif
#ifdef USE_PORTAUDIO
#include "pa.h"
#endif

namespace Ms {

#ifdef USE_PULSEAUDIO
extern Driver* getPulseAudioDriver(Seq*);
#endif

//---------------------------------------------------------
//   driverFactory
//    driver can be: jack alsa pulse portaudio
//---------------------------------------------------------

Driver* driverFactory(Seq* seq, QString driverName)
{
    Driver* driver = 0;
#if 1 // DEBUG: force "no audio"
    bool useJackFlag       = (preferences.useJackAudio || preferences.useJackMidi);
    bool useAlsaFlag       = preferences.useAlsaAudio;
    bool usePortaudioFlag  = preferences.usePortaudioAudio;
    bool usePulseAudioFlag = preferences.usePulseAudio;
    bool qaudio = false;

    if (!driverName.isEmpty()) {
        driverName        = driverName.toLower();
        useJackFlag       = false;
        useAlsaFlag       = false;
        usePortaudioFlag  = false;
        usePulseAudioFlag = false;
        if (driverName == "jack")
            useJackFlag = true;
        else if (driverName == "alsa")
            useAlsaFlag = true;
        else if (driverName == "pulse")
            usePulseAudioFlag = true;
        else if (driverName == "portaudio")
            usePortaudioFlag = true;
        else if (driverName == "qaudio")
            qaudio = true;
    }


    qDebug() << "Driver Name" << driverName << "use Jack" << useJackFlag;

//        useALSA       = false;
//        useJACK       = false;
//        usePortaudio  = false;
//        usePulseAudio = false;

#ifdef USE_PULSEAUDIO
    if (usePulseAudioFlag) {
        driver = getPulseAudioDriver(seq);
        if (!driver->init()) {
            qDebug("init PulseAudio failed");
            delete driver;
            driver = 0;
        }
        else
            usePulseAudio = true;
    }
#else
    (void)usePulseAudioFlag; // avoid compiler warning
#endif
#ifdef USE_PORTAUDIO
    if (usePortaudioFlag) {
        qDebug() << "PortAudio init";
        driver = new Portaudio(seq);
        if (!driver->init()) {
            qDebug("init PortAudio failed");
            delete driver;
            driver = 0;
        }
        else{
            qDebug() << "PortAudio init Ok";
            usePortaudio = true;
        }
    }
#else
    (void)usePortaudioFlag; // avoid compiler warning
#endif
#ifdef USE_ALSA
    if (driver == 0 && useAlsaFlag) {
        driver = new AlsaAudio(seq);
        if (!driver->init()) {
            qDebug("init ALSA driver failed");
            delete driver;
            driver = 0;
        }
        else {
            useALSA = true;
        }
    }
#else
    (void)useAlsaFlag; // avoid compiler warning
#endif
#ifdef USE_JACK
//#error "Compiling with jack"
    qDebug() << "Use jack" << useJackFlag;
    if (useJackFlag) {
        useAlsaFlag      = false;
        usePortaudioFlag = false;
        driver = new JackAudio(seq);
        if (!driver->init()) {
            qDebug("no JACK server found");
            delete driver;
            driver = 0;
        }
        else{
            qDebug() << "Jack init OK!";
            useJACK = true;
        }
    }
#else
    (void)useJackFlag; // avoid compiler warning
#endif
#endif

    if(qaudio){
        driver = new QAudioDriver(seq);
        if(!driver->init()){
            qDebug() << "Unable to Init QAudioDriver";
            delete driver;
            driver = 0;
        }else
            useQAudio = true;
    }



    if (driver == 0)
        qDebug("no audio driver found");

    return driver;
}

}

