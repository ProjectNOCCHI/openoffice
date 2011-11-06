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




#ifndef _XMLOFF_XMLTEXTMARKIMPORTCONTEXT_HXX
#define _XMLOFF_XMLTEXTMARKIMPORTCONTEXT_HXX

#include <xmloff/xmlictxt.hxx>
#include <com/sun/star/uno/Reference.h>


namespace com { namespace sun { namespace star {
	namespace text {
		class XTextRange;
        class XTextContent;
	}
	namespace xml { namespace sax {
		class XAttributeList;
	} }
} } }
namespace rtl {
	class OUString;
}
class XMLTextImportHelper;

class XMLFieldParamImportContext : public SvXMLImportContext
{
	XMLTextImportHelper& rHelper;
public:
	XMLFieldParamImportContext(
		SvXMLImport& rImport, 
		XMLTextImportHelper& rHlp,
		sal_uInt16 nPrfx,
		const ::rtl::OUString& rLocalName );

	virtual void StartElement(
		const ::com::sun::star::uno::Reference< 
			::com::sun::star::xml::sax::XAttributeList> & xAttrList);
};


/**
 * import bookmarks and reference marks
 * ( <bookmark>, <bookmark-start>, <bookmark-end>,
 *   <reference>, <reference-start>, <reference-end> )
 * 
 * All elements are handled by the same class due to their similarities.
 */
class XMLTextMarkImportContext : public SvXMLImportContext
{

    XMLTextImportHelper & m_rHelper;
    ::rtl::OUString m_sBookmarkName;
    ::rtl::OUString m_sFieldName;
    ::rtl::OUString m_sXmlId;
    // RDFa
    bool m_bHaveAbout;
    ::rtl::OUString m_sAbout;
    ::rtl::OUString m_sProperty;
    ::rtl::OUString m_sContent;
    ::rtl::OUString m_sDatatype;

public:

	TYPEINFO();

	XMLTextMarkImportContext(
		SvXMLImport& rImport, 
		XMLTextImportHelper& rHlp,
		sal_uInt16 nPrfx,
		const ::rtl::OUString& rLocalName );

protected:

	virtual void StartElement(
		const ::com::sun::star::uno::Reference< 
			::com::sun::star::xml::sax::XAttributeList> & xAttrList);
	virtual void EndElement();

    virtual SvXMLImportContext *CreateChildContext( sal_uInt16 nPrefix,
                                                    const ::rtl::OUString& rLocalName,
                                                    const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );

public:
    static ::com::sun::star::uno::Reference<
            ::com::sun::star::text::XTextContent > CreateAndInsertMark(
		SvXMLImport& rImport,
		const ::rtl::OUString& sServiceName,
		const ::rtl::OUString& sMarkName,
		const ::com::sun::star::uno::Reference<
			::com::sun::star::text::XTextRange> & rRange,
        const ::rtl::OUString& i_rXmlId = ::rtl::OUString());

    sal_Bool FindName(
		SvXMLImport& rImport,
		const ::com::sun::star::uno::Reference<
        ::com::sun::star::xml::sax::XAttributeList> & xAttrList);
};

#endif
