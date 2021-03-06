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

#ifndef SV4GUI_PURKINJENETWORKEDIT_H
#define SV4GUI_PURKINJENETWORKEDIT_H

//[dp] #include "sv4gui_MitkMesh.h"
#include "sv4gui_Model.h"

#include "sv4gui_DataNodeOperationInterface.h"
#include "sv4gui_LocalTableDelegate.h"
#include "sv4gui_Mesh.h"
#include "sv4gui_ProjectManager.h"
#include "sv4gui_PurkinjeNetworkMeshContainer.h"
#include "sv4gui_PurkinjeNetworkMeshMapper.h"
#include "sv4gui_PurkinjeNetwork1DContainer.h"
#include "sv4gui_PurkinjeNetwork1DMapper.h"
#include "sv4gui_PurkinjeNetworkInteractor.h"
#include "sv4gui_PurkinjeNetworkModel.h"

#include "sv4gui_QmitkFunctionality.h"

#include <itkEventObject.h>

#include <vtkSphereWidget.h>

#include <QWidget>
#include <QStandardItemModel>
#include <QItemDelegate>

namespace Ui {
class sv4guiPurkinjeNetworkEdit;
}

class sv4guiPurkinjeNetworkEdit : public sv4guiQmitkFunctionality
{
    Q_OBJECT

public:

    static const QString EXTENSION_ID;
    sv4guiPurkinjeNetworkEdit();
    virtual ~sv4guiPurkinjeNetworkEdit();

public slots:

    void showMesh(bool state);
    void showNetwork(bool state);
    void LoadMesh();
    void LoadParameters();
    void ExportParameters();
    void SelectMesh();
    void CreateNetwork();
    void MeshSurfaceName();
    void MeshSurfaceStartPoint();
    void MeshSurfaceSecondPoint();

    void AddObservers();

    void UpdateFaceSelection();
    void UpdateStartPointSelection();

    //void ShowModel(bool checked = false);

public:

    virtual void CreateQtPartControl(QWidget *parent) override;

    virtual void OnSelectionChanged(std::vector<mitk::DataNode*> nodes) override;
    virtual void NodeChanged(const mitk::DataNode* node) override;
    virtual void NodeAdded(const mitk::DataNode* node) override;
    virtual void NodeRemoved(const mitk::DataNode* node) override;

    void UpdateSphereData();

    virtual void Visible() override;
    virtual void Hidden() override;

    void SetModelParameters(sv4guiPurkinjeNetworkModel& pnetModel);
    void SetModelMesh(sv4guiPurkinjeNetworkModel& pnetModel);
    std::map<std::string, std::string> GetParametersFromGui();


protected:

    QWidget* m_Parent;

    Ui::sv4guiPurkinjeNetworkEdit *ui;


    QmitkStdMultiWidget* m_DisplayWidget;

    vtkSmartPointer<vtkSphereWidget> m_SphereWidget;

    bool m_UndoAble;

    sv4guiDataNodeOperationInterface* m_Interface;

    mitk::DataNode::Pointer m_ProjectFolderNode;
    mitk::DataStorage::Pointer m_DataStorage;
    QString m_StoreDir;

    sv4guiPurkinjeNetworkMeshContainer::Pointer m_MeshContainer;
    sv4guiPurkinjeNetworkMeshMapper::Pointer m_MeshMapper;
    mitk::DataNode::Pointer m_MeshNode;
    mitk::DataNode::Pointer m_MeshFolderNode;
    mitk::DataNode::Pointer m_ModelFolderNode;
    mitk::DataNode::Pointer m_PurkinjeNetworkNode;

    sv4guiPurkinjeNetwork1DContainer::Pointer m_1DContainer;
    sv4guiPurkinjeNetwork1DMapper::Pointer m_1DMapper;
    mitk::DataNode::Pointer m_1DNode;

    sv4guiMesh* LoadNetwork(std::string fileName);

private:

    QString m_MeshFileName;
    QString m_MeshOutputFileName;
    sv4guiMesh* m_SurfaceMesh;
    sv4guiMesh* m_SurfaceNetworkMesh;

    QString m_ParameterFileName;

    sv4guiProjectManager svProj;
    mitk::DataNode::Pointer m_ProjFolderNode;

    sv4guiPurkinjeNetworkInteractor::Pointer m_MeshInteractor;

    bool m_init = true;

    mitk::DataNode::Pointer getProjectNode();
    bool Initialize();
    void SetMeshInformation();
    sv4guiMesh* GetDataNodeMesh();
    mitk::DataNode::Pointer GetMeshFolderDataNode();
    mitk::DataNode::Pointer GetModelFolderDataNode();

    long m_MeshSelectFaceObserverTag;
    long m_MeshSelectStartPointObserverTag;
};

#endif // SV4GUI_PURKINJENETWORKEDIT_H
