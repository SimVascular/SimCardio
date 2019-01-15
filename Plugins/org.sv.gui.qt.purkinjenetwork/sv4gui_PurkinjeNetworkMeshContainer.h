/* Copyright (c) Stanford University, The Regents of the University of
 *               California, and others.
 *
 * All Rights Reserved.
 *
 * See Copyright-SimVascular.txt for additional details.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SV4GUI_PURKINJENETWORK_MESH_CONTAINER_H
#define SV4GUI_PURKINJENETWORK_MESH_CONTAINER_H

#include <iostream>
#include <vector>
#include "mitkBaseData.h"
#include "sv4gui_Mesh.h"

class sv4guiPurkinjeNetworkMeshContainer : public mitk::BaseData {

  public:

    mitkClassMacro(sv4guiPurkinjeNetworkMeshContainer, mitk::BaseData);
    itkFactorylessNewMacro(Self)
    itkCloneMacro(Self)

    void addStartSeed(double x, double y, double z);
    void addEndSeed(double x, double y, double z, int seedIndex);
    int getNumStartSeeds() const;
    int getNumEndSeeds(int startSeedIndex) const;
    std::vector<double> getStartSeed(int seedIndex) const;
    std::vector<double> getEndSeed(int startSeedIndex, int endSeedIndex) const;
    std::vector<int> findNearestSeed(double x, double y, double z, double tol);
    void deleteSeed(int startIndex, int endIndex);
    double distance(double x1,double y1,double z1,double x2,double y2,double z2) const;
    //virtual methods, that need to be implemented due to mitk::BaseData inheriting
    //from itk::DataObject
    //however if we dont intend to use this object with an itk filter we can leave them
    //empty
    virtual void UpdateOutputInformation() {};
    virtual void SetRequestedRegionToLargestPossibleRegion() {};
    virtual bool RequestedRegionIsOutsideOfTheBufferedRegion() { return false;};
    virtual bool VerifyRequestedRegion() { return true;};
    virtual void SetRequestedRegion(const itk::DataObject *data) {};

    std::vector<double> hoverPoint = std::vector<double>();

    void SetSurfaceMesh(sv4guiMesh* surfaceMesh);
    sv4guiMesh* GetSurfaceMesh();

    void SetModelFaces(std::vector<sv4guiModelElement::svFace*>& faces);
    std::vector<sv4guiModelElement::svFace*> GetModelFaces();

    void SetSurfaceNetwork(sv4guiMesh* surfaceNetwork);
    sv4guiMesh* GetSurfaceNetwork();

    mitk::Point3D getPickedPoint() { return m_currentPickedPoint; }
    void setPickedPoint(mitk::Point3D& point) { m_currentPickedPoint = point; }

    void SetModelElement(sv4guiModelElement* modelElement) { m_ModelElement = modelElement; {
    sv4guiModelElement* GetModelElement() { return m_ModelElement; }

protected:

  mitkCloneMacro(Self);
  sv4guiPurkinjeNetworkMeshContainer();
  sv4guiPurkinjeNetworkMeshContainer(const sv4guiPurkinjeNetworkMeshContainer& other);
  virtual ~sv4guiPurkinjeNetworkMeshContainer();

private:

  std::vector< std::vector<double> > m_startSeeds;
  std::vector< std::vector< std::vector<double> > > m_endSeeds;
  sv4guiMesh* m_SurfaceMesh;
  sv4guiMesh* m_SurfaceNetwork;
  mitk::Point3D m_currentPickedPoint;
  std::vector<sv4guiModelElement::svFace*> m_ModelFaces;
  sv4guiModelElement* m_ModelElement;

};

#endif //SV4GUI_PURKINJENETWORK_MESH_CONTAINER_H