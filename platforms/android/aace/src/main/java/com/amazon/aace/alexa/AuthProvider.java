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

// aace/alexa/AuthProvider.java
// This is an automatically generated file.

package com.amazon.aace.alexa;

import com.amazon.aace.core.PlatformInterface;

/**
 * AuthProvider should be extended to manage access tokens for AVS authorization and report
 * client authorization state to the Engine.
 */
abstract public class AuthProvider extends PlatformInterface
{
    /**
     * Describes the state of client authorization with AVS
     */
    public enum AuthState
    {
        /**
         * Authorization has not yet been acquired.
         * @hideinitializer
         */
        UNINITIALIZED("UNINITIALIZED"),
        /**
         * Authorization has been refreshed.
         * @hideinitializer
         */
        REFRESHED("REFRESHED"),
        /**
         * Authorization has expired.
         * @hideinitializer
         */
        EXPIRED("EXPIRED"),
        /**
         * Authorization has failed in a manner that cannot be corrected by retrying.
         * @hideinitializer
         */
        UNRECOVERABLE_ERROR("UNRECOVERABLE_ERROR");

        /**
         * @internal
         */
        private String m_name;

        /**
         * @internal
         */
        private AuthState( String name ) {
            m_name = name;
        }

        /**
         * @internal
         */
        public String toString() {
            return m_name;
        }
    }

    /**
     * Describes an error during an attempt to authorize with AVS
     */
    public enum AuthError
    {
        /**
         * No error encountered
         * @hideinitializer
         */
        NO_ERROR("NO_ERROR"),
        /**
         * An error was encountered, but no error description can be determined.
         * @hideinitializer
         */
        UNKNOWN_ERROR("UNKNOWN_ERROR"),
        /**
         * The client authorization failed.
         * @hideinitializer
         */
        AUTHORIZATION_FAILED("AUTHORIZATION_FAILED"),
        /**
         * The client is not authorized to use authorization codes.
         * @hideinitializer
         */
        UNAUTHORIZED_CLIENT("UNAUTHORIZED_CLIENT"),
        /**
         * The server encountered a runtime error.
         * @hideinitializer
         */
        SERVER_ERROR("SERVER_ERROR"),
        /**
         * The request is missing a required parameter, has an invalid value, or is otherwise malformed.
         * @hideinitializer
         */
        INVALID_REQUEST("INVALID_REQUEST"),
        /**
         * The authorization code is invalid, expired, revoked, or was issued to a different client.
         * @hideinitializer
         */
        AUTHORIZATION_EXPIRED("AUTHORIZATION_EXPIRED"),
        /**
         * The client specified the wrong token type.
         * @hideinitializer
         */
        UNSUPPORTED_GRANT_TYPE("UNSUPPORTED_GRANT_TYPE");

        /**
         * @internal
         */
        private String m_name;

        /**
         * @internal
         */
        private AuthError( String name ) {
            m_name = name;
        }

        /**
         * @internal
         */
        public String toString() {
            return m_name;
        }
    }

    /**
     * AuthProvider should be extended to manage access tokens for AVS authorization and report
     * client authorization state to the Engine.
     */
    public AuthProvider() {
    }

    /**
     * Returns the token used by the platform implementation for authorization with AVS.
     * The platform implementation should retrieve an auth token if it does not have one.
     *
     * @return The token used to authorize with AVS
     */
    public String getAuthToken() {
        return null;
    }

    /**
     * Returns the AVS authorization state of the platform implementation
     *
     * @return The AVS authorization state
     */
    public AuthState getAuthState() {
        return null;
    }

    /**
     * Notify the Engine that the Auth State/Error has changed
     *
     * @param [in] authState AuthState the authState of the platform implementation
     * @param [in] authError AuthError the authError of the platform implementation
     */
    public void authStateChange( AuthState authState, AuthError authError ) {
        authStateChange( getNativeObject(), authState, authError );
    }

    private native void authStateChange( long nativeObject, AuthState authState, AuthError authError );
}

// END OF FILE
