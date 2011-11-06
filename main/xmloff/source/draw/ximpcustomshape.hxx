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



#ifndef _XMLOFF_XIMPCUSTOMSHAPE_HXX_
#define _XMLOFF_XIMPCUSTOMSHAPE_HXX_

#include <xmloff/xmlictxt.hxx>
#include <xmloff/xmluconv.hxx>
#include <rtl/ustring.hxx>
#include <vector>
#include <com/sun/star/uno/Reference.h>
#include <com/sun/star/beans/PropertyValue.hpp>
#ifndef __com_sun_star_beans_PropertyValues_hpp__
#include <com/sun/star/beans/PropertyValues.hpp>
#endif
#include <com/sun/star/drawing/XShape.hpp>
#include <com/sun/star/drawing/EnhancedCustomShapeParameter.hpp>

namespace com { namespace sun { namespace star {
	namespace container { class XIndexContainer; }
	namespace beans { class XPropertySet; }
	namespace xml { namespace sax { class XAttributeList; } }
} } }

class SdXMLCustomShapeContext;
class XMLEnhancedCustomShapeContext : public SvXMLImportContext
{
	SvXMLUnitConverter& mrUnitConverter;
	com::sun::star::uno::Reference< com::sun::star::drawing::XShape >& mrxShape;
	std::vector< com::sun::star::beans::PropertyValue >& mrCustomShapeGeometry;

	std::vector< com::sun::star::beans::PropertyValue > maExtrusion;
	std::vector< com::sun::star::beans::PropertyValue > maPath;
	std::vector< com::sun::star::beans::PropertyValue > maTextPath;
	std::vector< com::sun::star::beans::PropertyValues > maHandles;
	std::vector< rtl::OUString > maEquations;
	std::vector< rtl::OUString > maEquationNames;

public:

	TYPEINFO();

	XMLEnhancedCustomShapeContext( SvXMLImport& rImport, ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape > &, sal_uInt16 nPrefix,
		const ::rtl::OUString& rLocalName, std::vector< com::sun::star::beans::PropertyValue >& rCustomShapeGeometry );

	virtual void StartElement( const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );
	virtual void EndElement();

	SvXMLImportContext *CreateChildContext( sal_uInt16 nPrefix, const ::rtl::OUString& rLocalName,
		const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList> & xAttrList );
};

#endif
