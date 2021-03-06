/* Copyright (C) 2011 Uni Osnabrück
 * This file is part of the LAS VEGAS Reconstruction Toolkit,
 *
 * LAS VEGAS is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * LAS VEGAS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA
 */


/*
 * Region.hpp
 *
 *  @date 18.08.2011
 *  @author Kim Rinnewitz (krinnewitz@uos.de)
 *  @author Sven Schalk (sschalk@uos.de)
 */

#ifndef REGION_H_
#define REGION_H_

#include "Vertex.hpp"
#include "Normal.hpp"
#include "HalfEdgeVertex.hpp"
#include "HalfEdgeFace.hpp"
#include <vector>
#include <stack>
#include <boost/shared_ptr.hpp>

namespace lvr {

template<typename VertexT, typename NormalT>
class HalfEdgeFace;

template<typename VertexT, typename NormalT>
class HalfEdgeVertex;

template<typename VertexT, typename NormalT>
class HalfEdgeMesh;


/**
 * @brief 	This class represents a region.
 */
template<typename VertexT, typename NormalT>
class Region
{

public:

	typedef HalfEdgeFace<VertexT, NormalT> HFace;
	typedef HalfEdgeVertex<VertexT, NormalT> HVertex;
	typedef HalfEdge<HVertex, HFace> HEdge;

	typedef HVertex*  VertexPtr;
	typedef HFace*    FacePtr;
	typedef HEdge*    EdgePtr;

	/**
	 * @brief constructor.
	 *
	 * @param 	region_number 	the number of the region
	 */
	Region(int regionNumber);

	/**
	 * @brief Adds a face to the region.
	 *
	 * @param	f	the face to add
	 */
	virtual void addFace(FacePtr f);

	/**
	 * @brief Removes a face from the region.
	 *
	 * @param	f	the face to remove
	 */
	virtual void deleteInvalidFaces();

	float getArea();

	/**
	 * @brief Sets this regions's label.
	 *
	 * @param label the label to set
	 */
	virtual void setLabel(std::string label);

	/**
	 * @brief Returns the regions's label.
	 */
	virtual std::string getLabel();

	/**
	 * @brief Returns true if region has a label.
	 */
	virtual bool hasLabel();

	/**
	 * @brief Finds all contours of the region (outer contour + holes)
	 *
	 * @param	epsilon	controls the number of points used for a contour
	 *
	 * @return 	a list of all contours
	 */
	virtual vector<vector<VertexT> > getContours(float epsilon);

	/**
	 * @brief caluclates a regression plane for the region and fits all faces into this plane
	 *
	 */
	virtual void regressionPlane();

	/**
	 * @brief tells if the given face is flickering
	 *
	 * @param	f	the face to test
	 *
	 * @return	true if the given face is flickering, false otherwise
	 *
	 */
	virtual bool detectFlicker(FacePtr f);

    /**
     * @brief the number of faces contained in this region
     */
    virtual size_t size();

	/**
	 * @brief destructor.
	 */
	virtual ~Region();

	/// Indicates if the region was dragged into a regression plane
	bool m_inPlane;

	bool m_unfinished;
	/// The faces in the region
	vector<FacePtr>    m_faces;

	/// The number of the region
	int m_regionNumber;

	/// The normal of the region (updated every time regressionPlane() is called)
	NormalT m_normal;
	
	///	The stuetzvektor of the plane
	VertexT m_stuetzvektor;

	/// indicates if the region is to be deleted or not
	bool m_toDelete;

	void calcArea();
private:

    /**
	 * @brief calculates a valid normal of the region
	 *
	 * @return a normal of the region
	 */
	virtual NormalT calcNormal();

	// The region's label
	std::string m_label;

	// Indicates whether the region has been labeled or not
	bool b_labeled;

	float m_area;

};
}

#include "Region.tcc"

#endif /* REGION_H_ */
