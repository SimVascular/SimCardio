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

#include "sv4gui_PurkinjeNetwork1DMapper.h"
#include "sv4gui_PurkinjeNetwork1DContainer.h"
#include "vtkPolyDataMapper.h"
#include "vtkSphereSource.h"
#include "vtkCubeSource.h"
#include <vtkDataSetMapper.h>

sv4guiPurkinjeNetwork1DMapper::sv4guiPurkinjeNetwork1DMapper()
{
  m_NewMesh = true;
}

sv4guiPurkinjeNetwork1DMapper::~sv4guiPurkinjeNetwork1DMapper()
{
}

//-------------------------
// GenerateDataForRenderer
//-------------------------
// Generate the data needed for rendering into renderer.
//
void sv4guiPurkinjeNetwork1DMapper::GenerateDataForRenderer(mitk::BaseRenderer* renderer)
{
  auto msgPrefix = "[sv4guiPurkinjeNetwork1DMapper::GenerateDataForRenderer] ";
  MITK_INFO << msgPrefix; 

  // make ls propassembly
  mitk::DataNode* node = GetDataNode();
  if (node == nullptr) {
    return;
  }
  LocalStorage* local_storage = m_LSH.GetLocalStorage(renderer);
  if (local_storage == nullptr) {
    MITK_INFO << msgPrefix << "local_storage is null";
    return;
  }

  bool visible = true;
  GetDataNode()->GetVisibility(visible, renderer, "visible");
  //MITK_INFO << msgPrefix << "visible " << visible;

  if (!visible) {
    local_storage->m_PropAssembly->VisibilityOff();
    return;
  }

  sv4guiPurkinjeNetwork1DContainer* mesh = 
    static_cast< sv4guiPurkinjeNetwork1DContainer* >( node->GetData() );

  if (mesh == nullptr) {
    local_storage->m_PropAssembly->VisibilityOff();
    return;
  }

  // [DaveP] Do we need to remove?
  // local_storage->m_PropAssembly->GetParts()->RemoveAllItems();

  // Show network mesh.
  //
  auto surfaceNetwork = mesh->GetSurfaceNetworkMesh();
  auto newMesh = mesh->IsNewSurfaceNetworkMesh();

  if ((surfaceNetwork != nullptr) && newMesh) {
    local_storage->m_PropAssembly->GetParts()->RemoveAllItems();
    //MITK_INFO << msgPrefix << "Have surface network data ";
    auto mesh = surfaceNetwork->GetVolumeMesh();
    vtkSmartPointer<vtkDataSetMapper> meshMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    meshMapper->SetInputData(mesh);
    vtkSmartPointer<vtkActor> polyMeshActor = vtkSmartPointer<vtkActor>::New();
    polyMeshActor->SetMapper(meshMapper);
    local_storage->m_PropAssembly->AddPart(polyMeshActor);
  }

  mesh->SetNewSurfaceNetworkMesh(false);
  local_storage->m_PropAssembly->VisibilityOn();
}

void sv4guiPurkinjeNetwork1DMapper::ResetMapper(mitk::BaseRenderer* renderer){
  LocalStorage *ls = m_LSH.GetLocalStorage(renderer);
  ls->m_PropAssembly->VisibilityOff();
}

vtkProp* sv4guiPurkinjeNetwork1DMapper::GetVtkProp(mitk::BaseRenderer* renderer)
{
  //MITK_INFO << "[sv4guiPurkinjeNetwork1DMapper::GetVtkProp] ";
  ResetMapper(renderer);
  GenerateDataForRenderer(renderer);
  LocalStorage *ls = m_LSH.GetLocalStorage(renderer);
  return ls->m_PropAssembly;
}
