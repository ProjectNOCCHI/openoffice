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



// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_package.hxx"
#include <ZipPackageEntry.hxx>
#include <com/sun/star/packages/zip/ZipConstants.hpp>
#include <osl/diagnose.h>

#include <ZipPackageFolder.hxx>
#include <ZipPackageStream.hxx>
#include <ContentInfo.hxx>

#include <comphelper/storagehelper.hxx>

using namespace rtl;
using namespace com::sun::star;
using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::container;
using namespace com::sun::star::packages::zip;
using namespace com::sun::star::packages::zip::ZipConstants;

ZipPackageEntry::ZipPackageEntry ( bool bNewFolder )
: mbIsFolder ( bNewFolder )
, mbAllowRemoveOnInsert( sal_True )
, pParent ( NULL )
{
}

ZipPackageEntry::~ZipPackageEntry()
{
	// When the entry is destroyed it must be already disconnected from the parent
	OSL_ENSURE( !pParent, "The parent must be disconnected already! Memory corruption is possible!\n" );
}

// XChild
OUString SAL_CALL ZipPackageEntry::getName(  ) 
	throw(RuntimeException)
{
	return msName;
}
void SAL_CALL ZipPackageEntry::setName( const OUString& aName ) 
	throw(RuntimeException)
{
	if ( pParent && msName.getLength() && pParent->hasByName ( msName ) )
		pParent->removeByName ( msName );

    // unfortunately no other exception than RuntimeException can be thrown here
    // usually the package is used through storage implementation, the problem should be detected there
    if ( !::comphelper::OStorageHelper::IsValidZipEntryFileName( aName, sal_True ) )
        throw RuntimeException( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( OSL_LOG_PREFIX "Unexpected character is used in file name." ) ), uno::Reference< XInterface >() );

	msName = aName;

	if ( pParent )
		pParent->doInsertByName ( this, sal_False );
}
uno::Reference< XInterface > SAL_CALL ZipPackageEntry::getParent(  ) 
		throw(RuntimeException)
{
	// return uno::Reference< XInterface >( xParent, UNO_QUERY );
	return uno::Reference< XInterface >( static_cast< ::cppu::OWeakObject* >( pParent ), UNO_QUERY );
}

void ZipPackageEntry::doSetParent ( ZipPackageFolder * pNewParent, sal_Bool bInsert )
{
	// xParent = pParent = pNewParent;
	pParent = pNewParent;
	if ( bInsert && msName.getLength() && !pNewParent->hasByName ( msName ) )
		pNewParent->doInsertByName ( this, sal_False );
}

void SAL_CALL ZipPackageEntry::setParent( const uno::Reference< XInterface >& xNewParent ) 
		throw(NoSupportException, RuntimeException)
{
	sal_Int64 nTest(0);
	uno::Reference < XUnoTunnel > xTunnel ( xNewParent, UNO_QUERY );
	if ( !xNewParent.is() || ( nTest = xTunnel->getSomething ( ZipPackageFolder::static_getImplementationId () ) ) == 0 )
		throw NoSupportException( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( OSL_LOG_PREFIX ) ), uno::Reference< uno::XInterface >() );

	ZipPackageFolder *pNewParent = reinterpret_cast < ZipPackageFolder * > ( nTest );

	if ( pNewParent != pParent )
	{
		if ( pParent && msName.getLength() && pParent->hasByName ( msName ) && mbAllowRemoveOnInsert )
			pParent->removeByName( msName );
		doSetParent ( pNewParent, sal_True );
	}
}
	//XPropertySet
uno::Reference< beans::XPropertySetInfo > SAL_CALL ZipPackageEntry::getPropertySetInfo(  ) 
		throw(RuntimeException)
{
	return uno::Reference < beans::XPropertySetInfo > ();
}
void SAL_CALL ZipPackageEntry::addPropertyChangeListener( const OUString& /*aPropertyName*/, const uno::Reference< beans::XPropertyChangeListener >& /*xListener*/ ) 
		throw(beans::UnknownPropertyException, WrappedTargetException, RuntimeException)
{
}
void SAL_CALL ZipPackageEntry::removePropertyChangeListener( const OUString& /*aPropertyName*/, const uno::Reference< beans::XPropertyChangeListener >& /*aListener*/ ) 
		throw(beans::UnknownPropertyException, WrappedTargetException, RuntimeException)
{
}
void SAL_CALL ZipPackageEntry::addVetoableChangeListener( const OUString& /*PropertyName*/, const uno::Reference< beans::XVetoableChangeListener >& /*aListener*/ ) 
		throw(beans::UnknownPropertyException, WrappedTargetException, RuntimeException)
{
}
void SAL_CALL ZipPackageEntry::removeVetoableChangeListener( const OUString& /*PropertyName*/, const uno::Reference< beans::XVetoableChangeListener >& /*aListener*/ ) 
		throw(beans::UnknownPropertyException, WrappedTargetException, RuntimeException)
{
}
