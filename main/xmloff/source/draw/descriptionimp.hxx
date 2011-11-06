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



#ifndef _XMLOFF_DESCRIPTIONIMP_HXX
#define _XMLOFF_DESCRIPTIONIMP_HXX

#include <xmloff/xmlictxt.hxx>
#include <com/sun/star/drawing/XShape.hpp>

//////////////////////////////////////////////////////////////////////////////
// office:events inside a shape

class SdXMLDescriptionContext : public SvXMLImportContext
{
private:
	com::sun::star::uno::Reference< com::sun::star::drawing::XShape > mxShape;
	::rtl::OUString msText;
public:
	TYPEINFO();

	SdXMLDescriptionContext( SvXMLImport& rImport, 
		sal_uInt16 nPrfx,
		const rtl::OUString& rLocalName, 
		const com::sun::star::uno::Reference< com::sun::star::xml::sax::XAttributeList>& xAttrList,
		const com::sun::star::uno::Reference< com::sun::star::drawing::XShape >& rxShape );
	virtual ~SdXMLDescriptionContext();

	virtual void EndElement();

	// This method is called for all characters that are contained in the
	// current element. The default is to ignore them.
	virtual void Characters( const ::rtl::OUString& rChars );
};

#endif	//  _XMLOFF_EVENTIMP_HXX

