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



#ifndef _XMLOFF_XFORMSINSTANCECONTEXT_HXX
#define _XMLOFF_XFORMSINSTANCECONTEXT_HXX


//
// include for parent class and members
//

#include "TokenContext.hxx"
#include <com/sun/star/uno/Reference.hxx>


//
// forward declarations
//

namespace com { namespace sun { namespace star {
    namespace xml { namespace sax { class XAttributeList; } }
    namespace xml { namespace dom { class XDocument; } }
    namespace beans { class XPropertySet; }
    namespace xforms { class XModel; }
} } }
namespace rtl { class OUString; }
class SvXMLImport;
class SvXMLImportContext;


/** import the xforms:instance element */
class XFormsInstanceContext : public TokenContext
{
    com::sun::star::uno::Reference<com::sun::star::xforms::XModel> mxModel;
    com::sun::star::uno::Reference<com::sun::star::xml::dom::XDocument> mxInstance;
    rtl::OUString msId;
    rtl::OUString msURL;

public:

    XFormsInstanceContext( SvXMLImport& rImport, 
                           sal_uInt16 nPrfx,
                           const ::rtl::OUString& rLName,
                           com::sun::star::uno::Reference<com::sun::star::beans::XPropertySet> xModel );
    virtual ~XFormsInstanceContext();


    //
    // implement SvXMLImportContext & TokenContext methods:
    // We override CreateChildContext, because we want to read
    // arbitrary DOM elements. For the attributes, we use the
    // TokenContext mechanism.
    //

	virtual SvXMLImportContext* CreateChildContext( 
        sal_uInt16 nPrefix,
        const rtl::OUString& rLocalName,
        const com::sun::star::uno::Reference<com::sun::star::xml::sax::XAttributeList >& xAttrList );

	virtual void EndElement();

protected:

    virtual void HandleAttribute( 
        sal_uInt16 nToken, 
        const rtl::OUString& rValue );

    virtual SvXMLImportContext* HandleChild( 
        sal_uInt16 nToken,
        sal_uInt16 nNamespace,
        const rtl::OUString& rLocalName,
        const com::sun::star::uno::Reference<com::sun::star::xml::sax::XAttributeList>& xAttrList );
};

#endif
