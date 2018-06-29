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

package com.amazon.aace.vehicle.config;

import android.util.Log;

import com.amazon.aace.core.config.EngineConfiguration;
import com.amazon.aace.core.config.StreamConfiguration;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;

/**
 * The @c VehicleConfiguration class is a factory interface for creating Vehicle service configuration objects.
 */
public class VehicleConfiguration {

    private static final String sTag = VehicleConfiguration.class.getSimpleName();

    /**
     * Specifies configurable vehicle properties
     */
    public enum VehiclePropertyType {
        /**
         * Vehicle make
         * @hideinitializer
         */
        MAKE("MAKE","make"),

        /**
         * Vehicle model
         * @hideinitializer
         */
        MODEL("MODEL","model"),

        /**
         * Vehicle year
         * @hideinitializer
         */
        YEAR("YEAR","year"),

        /**
         * Vehicle trim package
         * @hideinitializer
         */
        TRIM("TRIM","trim"),

        /**
         * Vehicle country (ISO country code)
         * @hideinitializer
         */
        GEOGRAPHY("GEOGRAPHY","geography"),

        /**
         * Software version
         * @hideinitializer
         */
        VERSION("VERSION","version"),

        /**
         * Operating system
         * @hideinitializer
         */
        OPERATING_SYSTEM("OPERATING_SYSTEM","os"),

        /**
         * Hardware architecture
         * @hideinitializer
         */
        HARDWARE_ARCH("HARDWARE_ARCH","arch"),

        /**
         * Language
         * @hideinitializer
         */
        LANGUAGE("LANGUAGE","language");

        /**
         * @internal
         */
        private String mName;

        /**
         * @internal
         */
        private String mKey;

        /**
         * Type used to identify a vehicle property type and value pair
         */
        VehiclePropertyType( String name, String key ) {
            mName = name;
            mKey = key;
        }

        /**
         * @internal
         */
        public String toString() {
            return mName;
        }

        /**
         * @internal
         */
        public String getKey() {
            return mKey;
        }
    }

    public static class VehicleProperty {
        private VehiclePropertyType mType;
        private String mValue;

        public VehicleProperty( VehiclePropertyType type, String value ) {
            mType = type;
            mValue = value;
        }

        public VehiclePropertyType getType() { return mType; }
        public String getValue() { return mValue; }
    }

    /**
     * Factory method used to programmatically generate vehicle info configuration data.
     * The data generated by this method is equivalent to providing the following JSON
     * values in a configuration file:
     *
     * @code    {.json}
     * {
     *   "aace.vehicle":
     *   {
     *      "info": {
     *          "make": "<MAKE>",
     *          "model": "<MODEL>",
     *          "year": "<YEAR>",
     *          "trim": "<TRIM>",
     *          "geography": "<GEOGRAPHY>",
     *          "version": "<SOFTWARE_VERSION>",
     *          "os": "<OPERATING_SYSTEM>",
     *          "arch": "<HARDWARE_ARCH>"
     *          "language": "<LANGUAGE>"
     *      }
     *   }
     * }
     * @endcode
     *
     * @param  propertyList A list of @c VehicleProperty type and value pairs
     */
    public static EngineConfiguration createVehicleInfoConfig( VehicleProperty[] propertyList ) {
        EngineConfiguration vehicleConfig = null;

        JSONObject config = new JSONObject();
        try {
            JSONObject aaceVehicleElement = new JSONObject();
            JSONObject infoElement = new JSONObject();

            for ( VehicleProperty next : propertyList ) {
                infoElement.put( next.getType().getKey(), next.getValue() );
            }

            aaceVehicleElement.put( "info", infoElement );
            config.put( "aace.vehicle", aaceVehicleElement );
        } catch ( JSONException e ) { Log.e( sTag, e.getMessage() ); }

        String configStr = config.toString();

        try ( InputStream is = new ByteArrayInputStream(
                configStr.getBytes( StandardCharsets.UTF_8.name() ) )
        ) {
            vehicleConfig = StreamConfiguration.create( is );
        } catch ( IOException e ) { Log.e( sTag, e.getMessage() ); }

        return vehicleConfig;
    }
}
