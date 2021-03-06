/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



#if ! defined INCLUDED_DP_COMMANDENVIRONMENTS_HXX
#define INCLUDED_DP_COMMANDENVIRONMENTS_HXX


#include "cppuhelper/compbase3.hxx"
//#include "cppuhelper/implbase2.hxx"
#include "ucbhelper/content.hxx"
#include "com/sun/star/uno/Type.hxx"


namespace css = ::com::sun::star;

namespace dp_manager {



/**
   This command environment is to be used when an extension is temporarily
   stored in the "tmp" repository. It prevents all kind of user interaction.
 */
class BaseCommandEnv
    : public ::cppu::WeakImplHelper3< css::ucb::XCommandEnvironment,
                                      css::task::XInteractionHandler,
                                      css::ucb::XProgressHandler >
{
protected:    
    css::uno::Reference< css::uno::XComponentContext > m_xContext;
    css::uno::Reference< css::task::XInteractionHandler> m_forwardHandler;

    void handle_(bool approve, bool abort,
                 css::uno::Reference< css::task::XInteractionRequest> const & xRequest );
public:
    virtual ~BaseCommandEnv();
    BaseCommandEnv();
    BaseCommandEnv(
        css::uno::Reference< css::task::XInteractionHandler> const & handler);

    // XCommandEnvironment
    virtual css::uno::Reference<css::task::XInteractionHandler > SAL_CALL
    getInteractionHandler() throw (css::uno::RuntimeException);
    virtual css::uno::Reference<css::ucb::XProgressHandler >
    SAL_CALL getProgressHandler() throw (css::uno::RuntimeException);

    // XInteractionHandler
    virtual void SAL_CALL handle(
        css::uno::Reference<css::task::XInteractionRequest > const & xRequest )
        throw (css::uno::RuntimeException);

    // XProgressHandler
    virtual void SAL_CALL push( css::uno::Any const & Status )
        throw (css::uno::RuntimeException);
    virtual void SAL_CALL update( css::uno::Any const & Status )
        throw (css::uno::RuntimeException);
    virtual void SAL_CALL pop() throw (css::uno::RuntimeException);
};

class TmpRepositoryCommandEnv : public BaseCommandEnv
{
public:
    TmpRepositoryCommandEnv();
    TmpRepositoryCommandEnv(css::uno::Reference< css::task::XInteractionHandler> const & handler);
    
// XInteractionHandler
    virtual void SAL_CALL handle(
        css::uno::Reference<css::task::XInteractionRequest > const & xRequest )
        throw (css::uno::RuntimeException);
    
};

/** this class is for use in XPackageManager::synchronize.

    It handles particular license cases.
 */
class LicenseCommandEnv : public BaseCommandEnv
{
private:
    ::rtl::OUString m_repository;
    bool m_bSuppressLicense;
public:
    LicenseCommandEnv(){};
    LicenseCommandEnv(
        css::uno::Reference< css::task::XInteractionHandler> const & handler,
        bool bSuppressLicense,
        ::rtl::OUString const & repository);
    
// XInteractionHandler
    virtual void SAL_CALL handle(
        css::uno::Reference<css::task::XInteractionRequest > const & xRequest )
        throw (css::uno::RuntimeException);
    
};

/** this class is for use in XPackageManager::checkPrerequisites

    It always prohibits a license interaction
 */
class NoLicenseCommandEnv : public BaseCommandEnv
{

public:
    NoLicenseCommandEnv(){};
    NoLicenseCommandEnv(css::uno::Reference< css::task::XInteractionHandler> const & handler);
    
// XInteractionHandler
    virtual void SAL_CALL handle(
        css::uno::Reference<css::task::XInteractionRequest > const & xRequest )
        throw (css::uno::RuntimeException);
    
};

/* For use in XExtensionManager::addExtension in the call to
   XPackage::checkPrerequisites
   It prevents all user interactions. The license is always accepted.
   It remembers if there was a platform or a dependency exception in
   the member m_bException. if there was any other exception then m_bUnknownException
   is set.
   
 */
class SilentCheckPrerequisitesCommandEnv : public BaseCommandEnv
{
public:
    SilentCheckPrerequisitesCommandEnv();
    // XInteractionHandler
    virtual void SAL_CALL handle(
        css::uno::Reference<css::task::XInteractionRequest > const & xRequest )
        throw (css::uno::RuntimeException);

    // Set to true if a PlatformException or a DependencyException were handled.
    css::uno::Any m_Exception;
    // Set to true if an unknown exception was handled.
    css::uno::Any m_UnknownException;    
};

// class NoExceptionCommandEnv : public BaseCommandEnv
// {
//     css::uno::Type m_type;
// public:
//     NoExceptionCommandEnv::NoExceptionCommandEnv(){};
//     NoExceptionCommandEnv::NoExceptionCommandEnv(
//         css::uno::Reference< css::task::XInteractionHandler> const & handler,
//         css::uno::Type const & type);
    
// // XInteractionHandler
//     virtual void SAL_CALL handle(
//         css::uno::Reference<css::task::XInteractionRequest > const & xRequest )
//         throw (css::uno::RuntimeException);
    
// };

}




#endif

