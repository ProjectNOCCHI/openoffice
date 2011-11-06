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



#ifndef _XMLOFF_XMLIMAGEMAPEXPORT_HXX_
#define _XMLOFF_XMLIMAGEMAPEXPORT_HXX_

#include <rtl/ustring.hxx>

namespace com { namespace sun { namespace star {
	namespace uno { template<class X> class Reference; }
	namespace beans { class XPropertySet; }
	namespace container { class XIndexContainer; }
} } }
class SvXMLExport;


/**
 * Export an ImageMap as defined by service com.sun.star.image.ImageMap to XML.
 */
class XMLImageMapExport
{
	const ::rtl::OUString msBoundary;
	const ::rtl::OUString msCenter;
	const ::rtl::OUString msDescription;
	const ::rtl::OUString msImageMap;
	const ::rtl::OUString msIsActive;
	const ::rtl::OUString msName;
	const ::rtl::OUString msPolygon;
	const ::rtl::OUString msRadius;
	const ::rtl::OUString msTarget;
	const ::rtl::OUString msURL;
	const ::rtl::OUString msTitle;

	SvXMLExport& mrExport;

	sal_Bool mbWhiteSpace;	/// use whitespace between image map elements?

public:
	XMLImageMapExport(SvXMLExport& rExport);

	~XMLImageMapExport();

	/**
	 * Get the ImageMap object from the "ImageMap" property and subsequently 
	 * export the map (if present).
	 */
	void Export( 
		/// the property set containing the ImageMap property
		const ::com::sun::star::uno::Reference<
			::com::sun::star::beans::XPropertySet> & rPropertySet);
	/**
	 * Export an ImageMap (XIndexContainer).
	 */
	void Export(
		/// the container containing the image map elements
		const ::com::sun::star::uno::Reference<
			::com::sun::star::container::XIndexContainer> & rContainer);

protected:

	/**
	 * Export a single, named map entry.
	 * (as given by com.sun.star.image.ImageMapObject)
	 * Calls methods for specific image map entries.
	 */
	void ExportMapEntry(
		const ::com::sun::star::uno::Reference<
			::com::sun::star::beans::XPropertySet> & rPropertySet);

	/**
	 * Export the specifics of a rectangular image map entry.
	 * To be called by ExportMapEntry.
	 */
	void ExportRectangle(
		const ::com::sun::star::uno::Reference<
			::com::sun::star::beans::XPropertySet> & rPropertySet);

	/**
	 * Export the specifics of a circular image map entry.
	 * To be called by ExportMapEntry.
	 */
	void ExportCircle(
		const ::com::sun::star::uno::Reference<
			::com::sun::star::beans::XPropertySet> & rPropertySet);

	/**
	 * Export the specifics of a polygonal image map entry; 
	 * To be called by ExportMapEntry.
	 */
	void ExportPolygon(
		const ::com::sun::star::uno::Reference<
			::com::sun::star::beans::XPropertySet> & rPropertySet);
};

#endif
