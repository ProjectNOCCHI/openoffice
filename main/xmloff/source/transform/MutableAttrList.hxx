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



#ifndef _XMLOFF_MUTABLEATTRLIST_HXX
#define _XMLOFF_MUTABLEATTRLIST_HXX

#include <com/sun/star/util/XCloneable.hpp>
#include <com/sun/star/xml/sax/XAttributeList.hpp>
#include <com/sun/star/lang/XUnoTunnel.hpp>

#include <cppuhelper/implbase3.hxx>

class SvXMLAttributeList;

class XMLMutableAttributeList : public ::cppu::WeakImplHelper3<
		::com::sun::star::xml::sax::XAttributeList,
		::com::sun::star::util::XCloneable,
		::com::sun::star::lang::XUnoTunnel>
{
	::com::sun::star::uno::Reference< 
		::com::sun::star::xml::sax::XAttributeList> m_xAttrList;

	SvXMLAttributeList *m_pMutableAttrList;

	SvXMLAttributeList *GetMutableAttrList();

public:
	XMLMutableAttributeList();
	XMLMutableAttributeList( const ::com::sun::star::uno::Reference< 
		::com::sun::star::xml::sax::XAttributeList> & rAttrList,
		   sal_Bool bClone=sal_False );
	~XMLMutableAttributeList();

	static const ::com::sun::star::uno::Sequence< sal_Int8 > & getUnoTunnelId() throw();

	// XUnoTunnel
    virtual sal_Int64 SAL_CALL getSomething( const ::com::sun::star::uno::Sequence< sal_Int8 >& aIdentifier ) throw(::com::sun::star::uno::RuntimeException);			 

	// ::com::sun::star::xml::sax::XAttributeList
	virtual sal_Int16 SAL_CALL getLength(void) throw( ::com::sun::star::uno::RuntimeException );
	virtual ::rtl::OUString SAL_CALL getNameByIndex(sal_Int16 i) throw( ::com::sun::star::uno::RuntimeException );
	virtual ::rtl::OUString SAL_CALL getTypeByIndex(sal_Int16 i) throw( ::com::sun::star::uno::RuntimeException );
	virtual ::rtl::OUString SAL_CALL getTypeByName(const ::rtl::OUString& aName) throw( ::com::sun::star::uno::RuntimeException );
	virtual ::rtl::OUString SAL_CALL getValueByIndex(sal_Int16 i) throw( ::com::sun::star::uno::RuntimeException );
	virtual ::rtl::OUString SAL_CALL getValueByName(const ::rtl::OUString& aName) throw( ::com::sun::star::uno::RuntimeException );

	// ::com::sun::star::util::XCloneable
	virtual ::com::sun::star::uno::Reference< ::com::sun::star::util::XCloneable > SAL_CALL createClone()	throw( ::com::sun::star::uno::RuntimeException );

	// methods that are not contained in any interface
	void SetValueByIndex( sal_Int16 i, const ::rtl::OUString& rValue );
	void AddAttribute( const ::rtl::OUString &sName , const ::rtl::OUString &sValue );
//	void Clear();
	void RemoveAttributeByIndex( sal_Int16 i );
	void RenameAttributeByIndex( sal_Int16 i, const ::rtl::OUString& rNewName );
//	void SetAttributeList( const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList > & );
	void AppendAttributeList( const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList > & );

	sal_Int16 GetIndexByName( const ::rtl::OUString& rName ) const;
};


#endif	//  _XMLOFF_MUTABLEATTRLIST_HXX
