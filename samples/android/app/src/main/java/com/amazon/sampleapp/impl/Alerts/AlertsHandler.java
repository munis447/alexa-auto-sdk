/*
 * Copyright 2017-2018 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

package com.amazon.sampleapp.impl.Alerts;

import android.app.Activity;
import android.view.View;
import android.widget.TextView;

import com.amazon.aace.alexa.Alerts;
import com.amazon.aace.alexa.MediaPlayer;
import com.amazon.aace.alexa.Speaker;
import com.amazon.sampleapp.R;
import com.amazon.sampleapp.impl.MediaPlayer.MediaPlayerHandler;
import com.amazon.sampleapp.impl.Logger.LoggerHandler;

public class AlertsHandler extends Alerts {

    private static final String sTag = "Alerts";

    private final Activity mActivity;
    private final LoggerHandler mLogger;
    private TextView mStateText;

    public AlertsHandler( Activity activity,
                          LoggerHandler logger,
                          MediaPlayer mediaPlayer,
                          Speaker speaker ) {
        super( mediaPlayer, speaker );
        mActivity = activity;
        mLogger = logger;
        setupGUI();
    }

    public AlertsHandler( Activity activity,
                          LoggerHandler logger,
                          MediaPlayerHandler mediaPlayer ) {
        this( activity, logger, mediaPlayer, mediaPlayer.getSpeaker() );
    }

    @Override
    public void alertStateChanged( final String alertToken,
                                   final AlertState state,
                                   final String reason ) {
        mLogger.postInfo( sTag, String.format( "Alert State Changed. STATE: %s, REASON: %s",
                state, reason ) );
        mActivity.runOnUiThread( new Runnable() {
            @Override
            public void run() { mStateText.setText( state != null ? state.toString() : "" ); }
        });
    }

    private void onLocalStop() {
        mLogger.postInfo( sTag, "Stopping active alert" );
        super.localStop();
    }

    private void onRemoveAllAlerts( ) {
        mLogger.postInfo( sTag, "Removing all pending alerts from storage" );
        super.removeAllAlerts();
    }

    private void setupGUI() {

        mStateText = mActivity.findViewById( R.id.alertState );

        mActivity.findViewById( R.id.stopAlertButton ).setOnClickListener(
            new View.OnClickListener() {
                @Override
                public void onClick( View v ) { onLocalStop(); }
            }
        );

        mActivity.findViewById( R.id.removeAlertsButton ).setOnClickListener(
            new View.OnClickListener() {
                @Override
                public void onClick( View v ) { onRemoveAllAlerts(); }
            }
        );
    }
}
