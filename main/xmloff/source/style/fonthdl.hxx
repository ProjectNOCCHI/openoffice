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



#ifndef XMLOFF_PROPERTYHANDLER_FONTTYPES_HXX
#define XMLOFF_PROPERTYHANDLER_FONTTYPES_HXX

#include <xmloff/xmlprhdl.hxx>

/**
    PropertyHandler for the XML-data-type:
*/
class XMLFontFamilyNamePropHdl : public XMLPropertyHandler
{
public:
	virtual ~XMLFontFamilyNamePropHdl();

	virtual sal_Bool importXML( const ::rtl::OUString& rStrImpValue, ::com::sun::star::uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const;
	virtual sal_Bool exportXML( ::rtl::OUString& rStrExpValue, const ::com::sun::star::uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const;
};

/**
    PropertyHandler for the XML-data-type:
*/
class XMLFontFamilyPropHdl : public XMLPropertyHandler
{
public:
	virtual ~XMLFontFamilyPropHdl();

	virtual sal_Bool importXML( const ::rtl::OUString& rStrImpValue, ::com::sun::star::uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const;
	virtual sal_Bool exportXML( ::rtl::OUString& rStrExpValue, const ::com::sun::star::uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const;
};

/**
    PropertyHandler for the XML-data-type:
*/
class XMLFontEncodingPropHdl : public XMLPropertyHandler
{
public:
	virtual ~XMLFontEncodingPropHdl();

	virtual sal_Bool importXML( const ::rtl::OUString& rStrImpValue, ::com::sun::star::uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const;
	virtual sal_Bool exportXML( ::rtl::OUString& rStrExpValue, const ::com::sun::star::uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const;
};

/**
    PropertyHandler for the XML-data-type:
*/
class XMLFontPitchPropHdl : public XMLPropertyHandler
{
public:
	virtual ~XMLFontPitchPropHdl();

	virtual sal_Bool importXML( const ::rtl::OUString& rStrImpValue, ::com::sun::star::uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const;
	virtual sal_Bool exportXML( ::rtl::OUString& rStrExpValue, const ::com::sun::star::uno::Any& rValue, const SvXMLUnitConverter& rUnitConverter ) const;
};


#endif // XMLOFF_PROPERTYHANDLER_FONTTYPES_HXX
