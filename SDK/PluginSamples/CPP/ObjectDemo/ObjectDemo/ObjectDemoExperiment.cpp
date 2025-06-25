// PlusTwoPhysicsExperiment.cpp : implementation file
//

#include "stdafx.h"
#include "ObjectDemoExperiment.h"
#include "ObjectDemoSimulation.h"
#include "AddinSimulationManager.h"
#include "PropSliderCtrl.h"

// CPlusTwoPhysicsExperiment
using namespace ATL;

CObjectDemoExperiment::CObjectDemoExperiment(CAddinSimulationManager* pManager)
{
	m_pManager = pManager;
}

CObjectDemoExperiment::~CObjectDemoExperiment()
{
}

void CObjectDemoExperiment::LoadAllExperiments()
{
	CComPtr<IExperimentTreeView> ExperimentTreeView;
	HRESULT HR = ExperimentTreeView.CoCreateInstance(CLSID_ExperimentTreeView);
	if (FAILED(HR))
	{
		return;
	}
	long SessionID = m_pManager->m_pAddin->m_lSessionID;
	ExperimentTreeView->DeleteAllExperiments(SessionID);
	ExperimentTreeView->SetRootNodeName(CString(CPP_SAMPLE_EXPERIMENT_TYPE_GROUP_1_PROPERTIES).AllocSysString(), TRUE);

#if FALSE //Will Implement this Later
	ExperimentTreeView->AddExperiment(SessionID, CString(MECHANICS_TREE_ROOT_TITLE).AllocSysString(), CString(MECHANICS_TREE_SIMPLE_PENDULUM_TITLE).AllocSysString());
	ExperimentTreeView->AddExperiment(SessionID, CString(MECHANICS_TREE_ROOT_TITLE).AllocSysString(), CString(MECHANICS_TREE_PROJECTILE_MOTION_TITLE).AllocSysString());
	ExperimentTreeView->AddExperiment(SessionID, CString(MECHANICS_TREE_ROOT_TITLE).AllocSysString(), CString(MECHANICS_TREE_PLANETORY_MOTION_TITLE).AllocSysString());
#endif //Will Implement this Later

	ExperimentTreeView->AddExperiment(SessionID, CString(OBJECT_3D_TREE_ROOT_TITLE).AllocSysString(), CString(OBJECT_3D_TREE_LEAF_PATTERN_TITLE).AllocSysString());

	ExperimentTreeView->Refresh();


}

void CObjectDemoExperiment::OnTreeNodeSelect(BSTR ExperimentGroup, BSTR ExperimentName)
{
	OnReloadExperiment(ExperimentGroup, ExperimentName);
}
void CObjectDemoExperiment::OnTreeNodeDblClick(BSTR ExperimentGroup, BSTR ExperimentName)
{
	if (CString(ExperimentGroup) == OBJECT_3D_TREE_ROOT_TITLE && CString(ExperimentName) == OBJECT_3D_TREE_LEAF_PATTERN_TITLE)
	{
		ShowObjectProperties();
	}
	else
	{
		m_pManager->ResetPropertyGrid();
	}
}
void CObjectDemoExperiment::OnReloadExperiment(BSTR ExperimentGroup, BSTR ExperimentName)
{
	if (CString(ExperimentGroup) == OBJECT_3D_TREE_ROOT_TITLE)
	{
		DrawObject(ExperimentName);
	}
	else
	{
		
	}

}



// CPlusTwoPhysicsExperiment member functions


void CObjectDemoExperiment::ShowObjectProperties()
{
#if TRUE
	CComPtr<IPropertyWindow> PropertyWindow;
	HRESULT HR = PropertyWindow.CoCreateInstance(CLSID_PropertyWindow);
	CString strGroupName = _T("");
	if (SUCCEEDED(HR))
	{
		PropertyWindow->RemoveAll();
		strGroupName = OBJECT_PROPERTIES_TITLE;
		PropertyWindow->AddPropertyGroup(strGroupName.AllocSysString());
		PropertyWindow->AddPropertyItemsAsString(strGroupName.AllocSysString(), OBJECT_TYPE_TITLE, OBJECT_TYPES, m_ObjectPattern.m_strObjectType.AllocSysString(), _T("Select the Object from the List"), FALSE);
		PropertyWindow->AddColorPropertyItem(strGroupName.AllocSysString(), OBJECT_COLOR_TITLE, m_ObjectPattern.m_Color, _T("Select the Color"));
		PropertyWindow->AddPropertyItemsAsString(strGroupName.AllocSysString(), OBJECT_SIMULATION_PATTERN_TITLE, OBJECT_PATTERN_TYPES, m_ObjectPattern.m_strSimulationPattern.AllocSysString(), _T("Select the Simulation Pattern"), FALSE);
		CString strInterval;
		strInterval.Format(_T("%d"), m_ObjectPattern.m_lSimulationInterval);
		PropertyWindow->AddPropertyItemAsString(strGroupName.AllocSysString(), OBJECT_SIMULATION_INTERVAL_TITLE, strInterval.AllocSysString(), _T("Simulation Interval In Milli Seconds"));


		PropertyWindow->EnableHeaderCtrl(FALSE);
		PropertyWindow->EnableDescriptionArea(TRUE);
		PropertyWindow->SetVSDotNetLook(TRUE);
		PropertyWindow->MarkModifiedProperties(TRUE, TRUE);

	}
#else //This shows all the property Options // But some methods has Bugs 
	CComPtr<IPropertyWindow> PropertyWindow;
	HRESULT HR = PropertyWindow.CoCreateInstance(CLSID_PropertyWindow);
	CString strGroupName = _T("");
	if (SUCCEEDED(HR))
	{
		PropertyWindow->RemoveAll();
		strGroupName = _T("Custom Group");
		PropertyWindow->AddPropertyGroup(strGroupName.AllocSysString());
		PropertyWindow->AddFilePathItem(strGroupName.AllocSysString(), _T("File Path"), _T("C:\\Test\\"), TRUE, _T("Icon Files(*.ico)|*.ico|All Files(*.*)|*.*||"), _T("ico"), _T("Select the File Path"));
		PropertyWindow->AddFilePathItem(strGroupName.AllocSysString(), _T("Folder Path"), _T("D:\\Test\\"), FALSE, _T(""), _T(""), _T("Select the Folder Path"));
		PropertyWindow->AddColorPropertyItem(strGroupName.AllocSysString(), _T("Select Color"), RGB(255, 0, 0), _T("Select the Color"));

		VARIANT DefaultValue, AddParam1, AddParam2, AddParam3, AddParam4;
		DefaultValue.vt = VT_BSTR;
		DefaultValue.bstrVal = _T("C:\\");
		AddParam1.vt = VT_BSTR;
		AddParam2.vt = VT_BSTR;
		AddParam3.vt = VT_BSTR;
		AddParam4.vt = VT_BSTR;

		PropertyWindow->AddHierarchyItem(_T("New Group"), _T("Sub Item Group1"), _T("Place"), _T("Enter Your Place"), NormalEdit, DefaultValue, AddParam1, AddParam2, AddParam3, AddParam4);
		PropertyWindow->AddHierarchyItem(_T("New Group"), _T("Sub Item Group1,Group 2"), _T("Name"), _T("Enter Your Name"), NormalEdit, DefaultValue, AddParam1, AddParam2, AddParam3, AddParam4);
		DefaultValue.bstrVal = _T("C:\\test.txt");
		AddParam1.bstrVal = _T("Icon Files(*.ico)|*.ico|All Files(*.*)|*.*||");
		AddParam2.bstrVal = _T("ico");
		PropertyWindow->AddHierarchyItem(_T("New Group"), _T("Sub Item Group1"), _T("File Path"), _T("Enter Your File Path"), FilePathEdit, DefaultValue, AddParam1, AddParam2, AddParam3, AddParam4);
		DefaultValue.bstrVal = _T("C:\\");
		PropertyWindow->AddHierarchyItem(_T("New Group"), _T("Sub Item Group1,Group 2"), _T("Folder Path"), _T("Enter Folder Path"), FolderPathEdit, DefaultValue, AddParam1, AddParam2, AddParam3, AddParam4);
		DefaultValue.vt = VT_UI4;
		DefaultValue.llVal = RGB(0, 255, 0);
		PropertyWindow->AddHierarchyItem(_T("New Group"), _T("Sub Item Group1"), _T("Default Color"), _T("Enter Your File Path"), ColorEdit, DefaultValue, AddParam1, AddParam2, AddParam3, AddParam4);

		DefaultValue.vt = VT_BSTR;
		DefaultValue.bstrVal = _T("Petrol");
		AddParam1.vt = VT_BSTR;
		AddParam1.bstrVal = _T("Diesel,Gas,Petrol,Electric");
		AddParam2.vt = VT_I4;
		AddParam2.llVal = FALSE;
		PropertyWindow->AddHierarchyItem(_T("New Group"), _T("Sub Item Group1,Group 2"), _T("Select Engine"), _T("Select Your Engines"), ComboEdit, DefaultValue, AddParam1, AddParam2, AddParam3, AddParam4);
		AddParam2.llVal = TRUE;
		PropertyWindow->AddHierarchyItem(_T("New Group"), _T("Sub Item Group1"), _T("Select Engine"), _T("Select The latest Engines"), ComboReadOnly, DefaultValue, AddParam1, AddParam2, AddParam3, AddParam4);

		CSliderProp* pProp = new CSliderProp(_T("Range Values"), 10, _T("Select the Range Values"));
		VARIANT VarControl;
		VarControl.vt = VT_BYREF;
		VarControl.byref = pProp;
		PropertyWindow->AddCustomPropertyItem(_T("New Group"), VarControl);


		PropertyWindow->EnableHeaderCtrl(FALSE);
		PropertyWindow->EnableDescriptionArea(TRUE);
		PropertyWindow->SetVSDotNetLook(TRUE);
		PropertyWindow->MarkModifiedProperties(TRUE, TRUE);


	}
	//This section demonstrates Other property Controls which is present in this Framework
#endif
	
}

void CObjectDemoExperiment::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		m_ObjectPattern.Serialize(ar);
	}
	else
	{
		m_ObjectPattern.Serialize(ar);
	}
}

void CObjectDemoExperiment::OnPropertyChanged(BSTR GroupName, BSTR PropertyName, BSTR PropertyValue)
{
	if (CString(GroupName) == OBJECT_PROPERTIES_TITLE)
	{
		m_ObjectPattern.OnPropertyChanged(GroupName, PropertyName, PropertyValue);
	}
	DrawScene();
}

void CObjectDemoExperiment::DrawScene()
{
	OnReloadExperiment(m_pManager->m_strExperimentGroup.AllocSysString(), m_pManager->m_strExperimentName.AllocSysString());
}


void CObjectDemoExperiment::DrawObject(CString ExperimentName)
{
	if (m_ObjectPattern.m_strObjectType == OBJECT_TYPE_CUBE)
	{
		DrawCube();
	}
	else if (m_ObjectPattern.m_strObjectType == OBJECT_TYPE_BALL)
	{
		DrawBall();
	}
	else if (m_ObjectPattern.m_strObjectType == OBJECT_TYPE_PYRAMID)
	{
		DrawPyramid();
	}
	else if (m_ObjectPattern.m_strObjectType == OBJECT_TYPE_AEROPLANE)
	{
		DrawAeroplane();
	}
	else if (m_ObjectPattern.m_strObjectType == OBJECT_TYPE_CLOCK)
	{
		DrawClock();
	}
	else if (m_ObjectPattern.m_strObjectType == OBJECT_TYPE_HELICOPTER)
	{
		DrawHelicopter();
	}
	else if (m_ObjectPattern.m_strObjectType == OBJECT_TYPE_CAT)
	{
		DrawCat();
	}
	else if (m_ObjectPattern.m_strObjectType == OBJECT_TYPE_Car)
	{
		DrawCar();
	}

}

void CObjectDemoExperiment::DrawHelicopter()
{
	CComPtr<IApplicationView> ApplicationView;
	HRESULT HR = ApplicationView.CoCreateInstance(CLSID_ApplicationView);
	if (FAILED(HR))
	{
		return;
	}

	const float bodyRadius = 0.2f;
	ApplicationView->InitializeEnvironment(TRUE);
	ApplicationView->BeginGraphicsCommands();

	// Set Background Color
	ApplicationView->SetBkgColor(GetRValue(m_ObjectPattern.m_Color) / 255.0f,
		GetGValue(m_ObjectPattern.m_Color) / 255.0f,
		GetBValue(m_ObjectPattern.m_Color) / 255.0f, 1.0f);

	HR = ApplicationView->StartNewDisplayList();
	if (HR == E_FAIL)
	{
		return;
	}

	// Initialize OpenGL View
	CComPtr<IOpenGLView> OpenGLView;
	HR = OpenGLView.CoCreateInstance(CLSID_OpenGLView);
	if (FAILED(HR))
	{
		return;
	}

	// Translate helicopter slightly
	OpenGLView->glTranslatef(0.0f, 0.0f, 0.0f);

	// ==== Draw Main Body (a simple elongated cube) ====
	OpenGLView->glColor3f(0.0f, 0.0f, 1.0f);
	OpenGLView->glBegin(GL_QUADS);
	// Front face
	OpenGLView->glVertex3f(-0.3f, -0.1f, 0.1f);
	OpenGLView->glVertex3f(0.3f, -0.1f, 0.1f);
	OpenGLView->glVertex3f(0.3f, 0.1f, 0.1f);
	OpenGLView->glVertex3f(-0.3f, 0.1f, 0.1f);
	// Back face
	OpenGLView->glVertex3f(-0.3f, -0.1f, -0.1f);
	OpenGLView->glVertex3f(0.3f, -0.1f, -0.1f);
	OpenGLView->glVertex3f(0.3f, 0.1f, -0.1f);
	OpenGLView->glVertex3f(-0.3f, 0.1f, -0.1f);
	// Connect sides
	OpenGLView->glVertex3f(-0.3f, -0.1f, 0.1f);
	OpenGLView->glVertex3f(-0.3f, -0.1f, -0.1f);
	OpenGLView->glVertex3f(-0.3f, 0.1f, -0.1f);
	OpenGLView->glVertex3f(-0.3f, 0.1f, 0.1f);

	OpenGLView->glVertex3f(0.3f, -0.1f, 0.1f);
	OpenGLView->glVertex3f(0.3f, -0.1f, -0.1f);
	OpenGLView->glVertex3f(0.3f, 0.1f, -0.1f);
	OpenGLView->glVertex3f(0.3f, 0.1f, 0.1f);

	OpenGLView->glVertex3f(-0.3f, 0.1f, 0.1f);
	OpenGLView->glVertex3f(0.3f, 0.1f, 0.1f);
	OpenGLView->glVertex3f(0.3f, 0.1f, -0.1f);
	OpenGLView->glVertex3f(-0.3f, 0.1f, -0.1f);

	OpenGLView->glVertex3f(-0.3f, -0.1f, 0.1f);
	OpenGLView->glVertex3f(0.3f, -0.1f, 0.1f);
	OpenGLView->glVertex3f(0.3f, -0.1f, -0.1f);
	OpenGLView->glVertex3f(-0.3f, -0.1f, -0.1f);
	OpenGLView->glEnd();

	// ==== Draw Tail Boom ====
	OpenGLView->glColor3f(0.3f, 0.3f, 0.8f);
	OpenGLView->glBegin(GL_LINES);
	OpenGLView->glVertex3f(0.3f, 0.0f, 0.0f);
	OpenGLView->glVertex3f(0.7f, 0.0f, 0.0f);
	OpenGLView->glEnd();

	// ==== Draw Top Rotor (Cross shape) ====
	OpenGLView->glColor3f(0.2f, 0.2f, 0.2f);
	OpenGLView->glBegin(GL_LINES);
	OpenGLView->glVertex3f(0.0f, 0.15f, -0.4f);
	OpenGLView->glVertex3f(0.0f, 0.15f, 0.4f);

	OpenGLView->glVertex3f(-0.4f, 0.15f, 0.0f);
	OpenGLView->glVertex3f(0.4f, 0.15f, 0.0f);
	OpenGLView->glEnd();

	// ==== Draw Tail Rotor ====
	OpenGLView->glColor3f(0.1f, 0.1f, 0.1f);
	OpenGLView->glBegin(GL_LINES);
	OpenGLView->glVertex3f(0.7f, 0.05f, -0.1f);
	OpenGLView->glVertex3f(0.7f, -0.05f, 0.1f);
	OpenGLView->glVertex3f(0.7f, -0.05f, -0.1f);
	OpenGLView->glVertex3f(0.7f, 0.05f, 0.1f);
	OpenGLView->glEnd();

	// ==== Draw Skids ====
	OpenGLView->glColor3f(0.0f, 0.0f, 0.0f);
	OpenGLView->glBegin(GL_LINES);
	// Left skid
	OpenGLView->glVertex3f(-0.2f, -0.15f, 0.2f);
	OpenGLView->glVertex3f(0.2f, -0.15f, 0.2f);

	// Right skid
	OpenGLView->glVertex3f(-0.2f, -0.15f, -0.2f);
	OpenGLView->glVertex3f(0.2f, -0.15f, -0.2f);

	// Connectors
	OpenGLView->glVertex3f(-0.2f, -0.1f, 0.1f);
	OpenGLView->glVertex3f(-0.2f, -0.15f, 0.2f);

	OpenGLView->glVertex3f(0.2f, -0.1f, 0.1f);
	OpenGLView->glVertex3f(0.2f, -0.15f, 0.2f);

	OpenGLView->glVertex3f(-0.2f, -0.1f, -0.1f);
	OpenGLView->glVertex3f(-0.2f, -0.15f, -0.2f);

	OpenGLView->glVertex3f(0.2f, -0.1f, -0.1f);
	OpenGLView->glVertex3f(0.2f, -0.15f, -0.2f);
	OpenGLView->glEnd();

	ApplicationView->EndNewDisplayList();
	ApplicationView->EndGraphicsCommands();
	ApplicationView->Refresh();
}

void CObjectDemoExperiment::DrawCat()
{
	CComPtr<IApplicationView> ApplicationView;
	HRESULT HR = ApplicationView.CoCreateInstance(CLSID_ApplicationView);
	if (FAILED(HR))
		return;

	ApplicationView->InitializeEnvironment(TRUE);
	ApplicationView->BeginGraphicsCommands();

	// Set background color
	ApplicationView->SetBkgColor(GetRValue(m_ObjectPattern.m_Color) / 255.0f,
		GetGValue(m_ObjectPattern.m_Color) / 255.0f,
		GetBValue(m_ObjectPattern.m_Color) / 255.0f,
		1.0f);

	HR = ApplicationView->StartNewDisplayList();
	if (HR == E_FAIL)
		return;

	CComPtr<IOpenGLView> OpenGLView;
	HR = OpenGLView.CoCreateInstance(CLSID_OpenGLView);
	if (FAILED(HR))
		return;

	OpenGLView->glTranslatef(0.0f, -0.2f, 0.0f);
	OpenGLView->glColor3f(0.8f, 0.6f, 0.4f);  // light brown for the cat

											  // === Body (Sphere approximation using triangle fan) ===
	const float radius = 0.2f;
	const int segments = 24;
	for (float phi = -1.57f; phi <= 1.57f; phi += 0.157f)  // vertical slices
	{
		OpenGLView->glBegin(GL_TRIANGLE_STRIP);
		for (int i = 0; i <= segments; i++)
		{
			float theta = (2.0f * 3.14159f * i) / segments;
			float x1 = cosf(theta) * cosf(phi);
			float y1 = sinf(phi);
			float z1 = sinf(theta) * cosf(phi);

			float x2 = cosf(theta) * cosf(phi + 0.157f);
			float y2 = sinf(phi + 0.157f);
			float z2 = sinf(theta) * cosf(phi + 0.157f);

			OpenGLView->glVertex3f(radius * x1, radius * y1, radius * z1);
			OpenGLView->glVertex3f(radius * x2, radius * y2, radius * z2);
		}
		OpenGLView->glEnd();
	}

	// === Head (Smaller sphere above body) ===
	OpenGLView->glPushMatrix();
	OpenGLView->glTranslatef(0.0f, 0.3f, 0.0f);
	for (float phi = -1.57f; phi <= 1.57f; phi += 0.157f)
	{
		OpenGLView->glBegin(GL_TRIANGLE_STRIP);
		for (int i = 0; i <= segments; i++)
		{
			float theta = (2.0f * 3.14159f * i) / segments;
			float x1 = cosf(theta) * cosf(phi);
			float y1 = sinf(phi);
			float z1 = sinf(theta) * cosf(phi);

			float x2 = cosf(theta) * cosf(phi + 0.157f);
			float y2 = sinf(phi + 0.157f);
			float z2 = sinf(theta) * cosf(phi + 0.157f);

			OpenGLView->glVertex3f(0.13f * x1, 0.13f * y1, 0.13f * z1);
			OpenGLView->glVertex3f(0.13f * x2, 0.13f * y2, 0.13f * z2);
		}
		OpenGLView->glEnd();
	}
	OpenGLView->glPopMatrix();

	// === Ears (Cones as triangle fans) ===
	OpenGLView->glColor3f(0.5f, 0.3f, 0.2f);
	auto DrawEar = [&](float offsetX)
	{
		OpenGLView->glPushMatrix();
		OpenGLView->glTranslatef(offsetX, 0.42f, 0.0f);
		OpenGLView->glBegin(GL_TRIANGLE_FAN);
		OpenGLView->glVertex3f(0.0f, 0.1f, 0.0f); // tip
		for (int i = 0; i <= segments; i++)
		{
			float angle = (2.0f * 3.14159f * i) / segments;
			float x = 0.05f * cosf(angle);
			float z = 0.05f * sinf(angle);
			OpenGLView->glVertex3f(x, 0.0f, z);
		}
		OpenGLView->glEnd();
		OpenGLView->glPopMatrix();
	};

	DrawEar(-0.08f); // Left ear
	DrawEar(0.08f); // Right ear

					// === Tail (curved cylinder using line strip) ===
	OpenGLView->glColor3f(0.7f, 0.5f, 0.3f);
	OpenGLView->glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 30; i++)
	{
		float angle = i * 0.1f;
		OpenGLView->glVertex3f(-0.2f + 0.05f * cos(angle), -0.1f + 0.01f * i, 0.05f * sin(angle));
	}
	OpenGLView->glEnd();

	// === Eyes (flat small quads) ===
	OpenGLView->glColor3f(0.0f, 0.0f, 0.0f);
	OpenGLView->glBegin(GL_QUADS);
	OpenGLView->glVertex3f(-0.05f, 0.32f, 0.13f);
	OpenGLView->glVertex3f(-0.03f, 0.32f, 0.13f);
	OpenGLView->glVertex3f(-0.03f, 0.34f, 0.13f);
	OpenGLView->glVertex3f(-0.05f, 0.34f, 0.13f);

	OpenGLView->glVertex3f(0.03f, 0.32f, 0.13f);
	OpenGLView->glVertex3f(0.05f, 0.32f, 0.13f);
	OpenGLView->glVertex3f(0.05f, 0.34f, 0.13f);
	OpenGLView->glVertex3f(0.03f, 0.34f, 0.13f);
	OpenGLView->glEnd();

	ApplicationView->EndNewDisplayList();
	ApplicationView->EndGraphicsCommands();
	ApplicationView->Refresh();
}


void CObjectDemoExperiment::DrawCar()
{
	CComPtr<IApplicationView> ApplicationView;
	HRESULT HR = ApplicationView.CoCreateInstance(CLSID_ApplicationView);
	if (FAILED(HR))
	{
		return;
	}

	ApplicationView->ResetScene();
	ApplicationView->InitializeEnvironment(TRUE);
	ApplicationView->BeginGraphicsCommands();

	// Set Background Color
	ApplicationView->SetBkgColor(
		GetRValue(m_ObjectPattern.m_Color) / 255.0f,
		GetGValue(m_ObjectPattern.m_Color) / 255.0f,
		GetBValue(m_ObjectPattern.m_Color) / 255.0f,
		1.0f);

	HR = ApplicationView->StartNewDisplayList();
	if (HR == E_FAIL)
	{
		return;
	}

	// Create OpenGLView
	CComPtr<IOpenGLView> OpenGLView;
	HR = OpenGLView.CoCreateInstance(CLSID_OpenGLView);
	if (FAILED(HR))
	{
		return;
	}

	// Base translation
	OpenGLView->glTranslatef(0.0f, 0.0f, 0.0f);

	// --- Car Base Body ---
	OpenGLView->glColor3f(0.8f, 0.0f, 0.0f); // red
	OpenGLView->glBegin(GL_QUADS);

	// Bottom
	OpenGLView->glVertex3f(-1.0f, -0.25f, 0.5f);
	OpenGLView->glVertex3f(1.0f, -0.25f, 0.5f);
	OpenGLView->glVertex3f(1.0f, -0.25f, -0.5f);
	OpenGLView->glVertex3f(-1.0f, -0.25f, -0.5f);

	// Top
	OpenGLView->glVertex3f(-1.0f, 0.25f, 0.5f);
	OpenGLView->glVertex3f(1.0f, 0.25f, 0.5f);
	OpenGLView->glVertex3f(1.0f, 0.25f, -0.5f);
	OpenGLView->glVertex3f(-1.0f, 0.25f, -0.5f);

	// Front (X = +1.0f)
	OpenGLView->glVertex3f(1.0f, -0.25f, 0.5f);
	OpenGLView->glVertex3f(1.0f, 0.25f, 0.5f);
	OpenGLView->glVertex3f(1.0f, 0.25f, -0.5f);
	OpenGLView->glVertex3f(1.0f, -0.25f, -0.5f);

	// Back (X = -1.0f)
	OpenGLView->glVertex3f(-1.0f, -0.25f, 0.5f);
	OpenGLView->glVertex3f(-1.0f, 0.25f, 0.5f);
	OpenGLView->glVertex3f(-1.0f, 0.25f, -0.5f);
	OpenGLView->glVertex3f(-1.0f, -0.25f, -0.5f);

	// Left (Z = +0.5f)
	OpenGLView->glVertex3f(-1.0f, -0.25f, 0.5f);
	OpenGLView->glVertex3f(-1.0f, 0.25f, 0.5f);
	OpenGLView->glVertex3f(1.0f, 0.25f, 0.5f);
	OpenGLView->glVertex3f(1.0f, -0.25f, 0.5f);

	// Right (Z = -0.5f)
	OpenGLView->glVertex3f(-1.0f, -0.25f, -0.5f);
	OpenGLView->glVertex3f(-1.0f, 0.25f, -0.5f);
	OpenGLView->glVertex3f(1.0f, 0.25f, -0.5f);
	OpenGLView->glVertex3f(1.0f, -0.25f, -0.5f);

	OpenGLView->glEnd();

	// --- Roof Box ---
	OpenGLView->glColor3f(0.3f, 0.3f, 0.3f); // dark gray
	OpenGLView->glBegin(GL_QUADS);

	// Bottom
	OpenGLView->glVertex3f(-0.6f, 0.25f, 0.3f);
	OpenGLView->glVertex3f(0.6f, 0.25f, 0.3f);
	OpenGLView->glVertex3f(0.6f, 0.25f, -0.3f);
	OpenGLView->glVertex3f(-0.6f, 0.25f, -0.3f);

	// Top
	OpenGLView->glVertex3f(-0.6f, 0.55f, 0.3f);
	OpenGLView->glVertex3f(0.6f, 0.55f, 0.3f);
	OpenGLView->glVertex3f(0.6f, 0.55f, -0.3f);
	OpenGLView->glVertex3f(-0.6f, 0.55f, -0.3f);

	// Left side (Z = +0.3)
	OpenGLView->glVertex3f(-0.6f, 0.25f, 0.3f);
	OpenGLView->glVertex3f(-0.6f, 0.55f, 0.3f);
	OpenGLView->glVertex3f(0.6f, 0.55f, 0.3f);
	OpenGLView->glVertex3f(0.6f, 0.25f, 0.3f);

	// Right side (Z = -0.3)
	OpenGLView->glVertex3f(-0.6f, 0.25f, -0.3f);
	OpenGLView->glVertex3f(-0.6f, 0.55f, -0.3f);
	OpenGLView->glVertex3f(0.6f, 0.55f, -0.3f);
	OpenGLView->glVertex3f(0.6f, 0.25f, -0.3f);

	// Back (X = -0.6f)
	OpenGLView->glVertex3f(-0.6f, 0.25f, 0.3f);
	OpenGLView->glVertex3f(-0.6f, 0.55f, 0.3f);
	OpenGLView->glVertex3f(-0.6f, 0.55f, -0.3f);
	OpenGLView->glVertex3f(-0.6f, 0.25f, -0.3f);

	OpenGLView->glEnd();

	// --- Front Transparent Windshield (X = +0.6f) ---
	OpenGLView->glEnable(GL_BLEND);
	OpenGLView->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	OpenGLView->glColor4f(0.5f, 0.8f, 1.0f, 0.3f); // transparent light blue

	OpenGLView->glBegin(GL_QUADS);
	OpenGLView->glVertex3f(0.6f, 0.25f, 0.3f);
	OpenGLView->glVertex3f(0.6f, 0.55f, 0.3f);
	OpenGLView->glVertex3f(0.6f, 0.55f, -0.3f);
	OpenGLView->glVertex3f(0.6f, 0.25f, -0.3f);
	OpenGLView->glEnd();

	OpenGLView->glDisable(GL_BLEND);

	// --- Wheels ---
	const float wheel_radius = 0.2f;
	const int segments = 16;

	auto DrawWheel = [&](float x, float y, float z)
	{
		OpenGLView->glPushMatrix();
		OpenGLView->glTranslatef(x, y, z);
		OpenGLView->glColor3f(0.1f, 0.1f, 0.1f); // black
		OpenGLView->glBegin(GL_TRIANGLE_FAN);
		OpenGLView->glVertex3f(0.0f, 0.0f, 0.0f);
		for (int i = 0; i <= segments; ++i)
		{
			float angle = (2.0f * 3.1415926f * i) / segments;
			float dx = cosf(angle) * wheel_radius;
			float dy = sinf(angle) * wheel_radius;
			OpenGLView->glVertex3f(dx, dy, 0.0f);
		}
		OpenGLView->glEnd();
		OpenGLView->glPopMatrix();
	};

	// Front-left, front-right, rear-left, rear-right
	DrawWheel(-0.7f, -0.35f, 0.6f);
	DrawWheel(0.7f, -0.35f, 0.6f);
	DrawWheel(-0.7f, -0.35f, -0.6f);
	DrawWheel(0.7f, -0.35f, -0.6f);

	ApplicationView->EndNewDisplayList();
	ApplicationView->EndGraphicsCommands();
	ApplicationView->Refresh();
}


void CObjectDemoExperiment::DrawCube()
{
	
	CComPtr<IApplicationView> ApplicationView;
	HRESULT HR = ApplicationView.CoCreateInstance(CLSID_ApplicationView);
	if (FAILED(HR))
	{
		return;
	}

	//We can use all the normal OpenGL API defined in the standard Opengl header file
	const float radius = 0.34f;
	
	ApplicationView->InitializeEnvironment(TRUE);
	ApplicationView->BeginGraphicsCommands();
	
	//Set the Background Color
	ApplicationView->SetBkgColor(GetRValue(m_ObjectPattern.m_Color) / (float)255.0, GetGValue(m_ObjectPattern.m_Color) / (float)255.0,
		GetBValue(m_ObjectPattern.m_Color) / (float)255.0, 1.0);

	HR = ApplicationView->StartNewDisplayList();
	if (HR == E_FAIL)
	{
		return;
	}

	//Draw using Native IOpenGLView Interface
	CComPtr<IOpenGLView> OpenGLView;
	HR = OpenGLView.CoCreateInstance(CLSID_OpenGLView);
	if (FAILED(HR))
	{
		return;
	}
	

	OpenGLView->glBegin(GL_QUAD_STRIP);
		OpenGLView->glColor3f(1.0f, 0.0f, 1.0f);
		OpenGLView->glVertex3f(-0.3f, 0.3f, 0.3f);
		OpenGLView->glColor3f(1.0f, 0.0f, 0.0f);
		OpenGLView->glVertex3f(-0.3f, -0.3f, 0.3f);
		OpenGLView->glColor3f(1.0f, 1.0f, 1.0f);
		OpenGLView->glVertex3f(0.3f, 0.3f, 0.3f);
		OpenGLView->glColor3f(1.0f, 1.0f, 0.0f);
		OpenGLView->glVertex3f(0.3f, -0.3f, 0.3f);
		OpenGLView->glColor3f(0.0f, 1.0f, 1.0f);
		OpenGLView->glVertex3f(0.3f, 0.3f, -0.3f);
		OpenGLView->glColor3f(0.0f, 1.0f, 0.0f);
		OpenGLView->glVertex3f(0.3f, -0.3f, -0.3f);
		OpenGLView->glColor3f(0.0f, 0.0f, 1.0f);
		OpenGLView->glVertex3f(-0.3f, 0.3f, -0.3f);
		OpenGLView->glColor3f(0.0f, 0.0f, 0.0f);
		OpenGLView->glVertex3f(-0.3f, -0.3f, -0.3f);
		OpenGLView->glColor3f(1.0f, 0.0f, 1.0f);
		OpenGLView->glVertex3f(-0.3f, 0.3f, 0.3f);
		OpenGLView->glColor3f(1.0f, 0.0f, 0.0f);
		OpenGLView->glVertex3f(-0.3f, -0.3f, 0.3f);
	OpenGLView->glEnd();

	OpenGLView->glBegin(GL_QUADS);
		OpenGLView->glColor3f(1.0f, 0.0f, 1.0f);
		OpenGLView->glVertex3f(-0.3f, 0.3f, 0.3f);
		OpenGLView->glColor3f(1.0f, 1.0f, 1.0f);
		OpenGLView->glVertex3f(0.3f, 0.3f, 0.3f);
		OpenGLView->glColor3f(0.0f, 1.0f, 1.0f);
		OpenGLView->glVertex3f(0.3f, 0.3f, -0.3f);
		OpenGLView->glColor3f(0.0f, 0.0f, 1.0f);
		OpenGLView->glVertex3f(-0.3f, 0.3f, -0.3f);
		OpenGLView->glColor3f(1.0f, 0.0f, 0.0f);
		OpenGLView->glVertex3f(-0.3f, -0.3f, 0.3f);
		OpenGLView->glColor3f(0.0f, 0.0f, 0.0f);
		OpenGLView->glVertex3f(-0.3f, -0.3f, -0.3f);
		OpenGLView->glColor3f(0.0f, 1.0f, 0.0f);
		OpenGLView->glVertex3f(0.3f, -0.3f, -0.3f);
		OpenGLView->glColor3f(1.0f, 1.0f, 0.0f);
		OpenGLView->glVertex3f(0.3f, -0.3f, 0.3f);

	OpenGLView->glEnd();

	OpenGLView->glColor3f(1.f, 1.f, 1.f);
	OpenGLView->glRasterPos3f(-radius, radius, radius);
	OpenGLView->glRasterPos3f(-radius, -radius, radius);
	OpenGLView->glRasterPos3f(radius, radius, radius);
	OpenGLView->glRasterPos3f(radius, -radius, radius);
	OpenGLView->glRasterPos3f(radius, radius, -radius);
	OpenGLView->glRasterPos3f(radius, -radius, -radius);
	OpenGLView->glRasterPos3f(-radius, radius, -radius);
	OpenGLView->glRasterPos3f(-radius, -radius, -radius);
	
	//Set the Inner Sphere Color
	
	
	ApplicationView->EndNewDisplayList();
	ApplicationView->EndGraphicsCommands();
	ApplicationView->Refresh();
	
}


void CObjectDemoExperiment::DrawBall()
{
	//Draw using ApplicationView Interface
	CComPtr<IApplicationView> ApplicationView;
	HRESULT HR = ApplicationView.CoCreateInstance(CLSID_ApplicationView);
	if (FAILED(HR))
	{
		return;
	}

	ApplicationView->InitializeEnvironment(TRUE);
	ApplicationView->BeginGraphicsCommands();

	//Set the Background Color
	ApplicationView->SetBkgColor(GetRValue(m_ObjectPattern.m_Color) / (float)255, GetGValue(m_ObjectPattern.m_Color) / (float)255,
		GetBValue(m_ObjectPattern.m_Color) / (float)255, 1);

	int SECTIONS = 25;
	double RADIUS = 1.0;
	
	HR = ApplicationView->StartNewDisplayList();
	if (HR == E_FAIL)
	{
		return;
	}

	ApplicationView->SetColorf(0.0f, 0.0f, 1.0f);
	
	ApplicationView->DrawSphere(RADIUS, SECTIONS, SECTIONS);
	//Draw One more spehere inside it
	
	ApplicationView->SetColorf(1.0f, 1.0f, 1.0f);

	ApplicationView->DrawSphere(RADIUS/1.5, SECTIONS, SECTIONS);

	ApplicationView->EndNewDisplayList();
	ApplicationView->EndGraphicsCommands();
	ApplicationView->Refresh();
}


void CObjectDemoExperiment::DrawPyramid()
{
	CComPtr<IApplicationView> ApplicationView;
	HRESULT HR = ApplicationView.CoCreateInstance(CLSID_ApplicationView);
	if (FAILED(HR))
	{
		return;
	}

	//We can use all the normal OpenGL API defined in the standard Opengl header file
	const float radius = 0.34f;
	ApplicationView->ResetScene();
	ApplicationView->InitializeEnvironment(TRUE);
	ApplicationView->BeginGraphicsCommands();

	//Set the Background Color
	ApplicationView->SetBkgColor(GetRValue(m_ObjectPattern.m_Color) / (float)255, GetGValue(m_ObjectPattern.m_Color) / (float)255,
		GetBValue(m_ObjectPattern.m_Color) / (float)255, 1);

	HR = ApplicationView->StartNewDisplayList();
	if (HR == E_FAIL)
	{
		return;
	}

	//Draw using Native IOpenGLView Interface
	CComPtr<IOpenGLView> OpenGLView;
	HR = OpenGLView.CoCreateInstance(CLSID_OpenGLView);
	if (FAILED(HR))
	{
		return;
	}

	OpenGLView->glTranslatef(0.01f, 0.f, 0.01f);
	OpenGLView->glColor3f(0.0f, 0.4f, 0.8f);

	// We're telling OpenGL that we want to render triangles.
	OpenGLView->glBegin(GL_TRIANGLES);

		// Each of the pyramid's faces will have 3 vertices.
		// We'll start drawing at the top, then go down to the bottom left,
		// then to the right.

		// When we start our next triangle, we're going to be going back to
		// the top-middle. Imagine drawing a pyramid without ever lifting your
		// pen up.

		// New Triangle - Front
		OpenGLView->glColor3f(1.0f, 0.0f, 0.0f);
		OpenGLView->glVertex3f(0.0f, 1.0f, 0.0f);

		OpenGLView->glColor3f(0.0f, 1.0f, 0.0f);
		OpenGLView->glVertex3f(-1.0f, -1.0f, 1.0f);

		OpenGLView->glColor3f(0.0f, 0.0f, 1.0f);
		OpenGLView->glVertex3f(1.0f, -1.0f, 1.0f);

		// New Triangle - Right
		OpenGLView->glColor3f(1.0f, 0.0f, 0.0f);
		OpenGLView->glVertex3f(0.0f, 1.0f, 0.0f);

		OpenGLView->glColor3f(0.0f, 1.0f, 0.0f);
		OpenGLView->glVertex3f(1.0f, -1.0f, 1.0f);

		OpenGLView->glColor3f(0.0f, 0.0f, 1.0f);
		OpenGLView->glVertex3f(1.0f, -1.0f, -1.0f);

		// New Triangle - Back
		OpenGLView->glColor3f(1.0f, 0.0f, 0.0f);
		OpenGLView->glVertex3f(0.0f, 1.0f, 0.0f);

		OpenGLView->glColor3f(0.0f, 1.0f, 0.0f);
		OpenGLView->glVertex3f(1.0f, -1.0f, -1.0f);

		OpenGLView->glColor3f(0.0f, 0.0f, 1.0f);
		OpenGLView->glVertex3f(-1.0f, -1.0f, -1.0f);

		// New Triangle - left
		OpenGLView->glColor3f(1.0f, 0.0f, 0.0f);
		OpenGLView->glVertex3f(0.0f, 1.0f, 0.0f);

		OpenGLView->glColor3f(0.0f, 1.0f, 0.0f);
		OpenGLView->glVertex3f(-1.0f, -1.0f, -1.0f);

		OpenGLView->glColor3f(0.0f, 0.0f, 1.0f);
		OpenGLView->glVertex3f(-1.0f, -1.0f, 1.0f);

		// New Triangle - Bottom 1
		OpenGLView->glColor3f(1.0f, 0.0f, 0.0f);
		OpenGLView->glVertex3f(-1.0f, -1.0f, 1.0f);

		OpenGLView->glColor3f(0.0f, 1.0f, 0.0f);
		OpenGLView->glVertex3f(1.0f, -1.0f, 1.0f);

		OpenGLView->glColor3f(0.0f, 0.0f, 1.0f);
		OpenGLView->glVertex3f(-1.0f, -1.0f, -1.0f);

		// New Triangle - Bottom 2
		OpenGLView->glColor3f(1.0f, 0.0f, 0.0f);
		OpenGLView->glVertex3f(-1.0f, -1.0f, -1.0f);      // Note: we're starting from the last point
											  // of the previous triangle.

		OpenGLView->glColor3f(0.0f, 1.0f, 0.0f);
		OpenGLView->glVertex3f(1.0f, -1.0f, -1.0f);

		OpenGLView->glColor3f(0.0f, 0.0f, 1.0f);
		OpenGLView->glVertex3f(1.0f, -1.0f, 1.0f);

	OpenGLView->glEnd();

	ApplicationView->EndNewDisplayList();
	ApplicationView->EndGraphicsCommands();
	ApplicationView->Refresh();

}


void CObjectDemoExperiment::DrawAeroplane()
{
	CComPtr<IApplicationView> ApplicationView;
	HRESULT HR = ApplicationView.CoCreateInstance(CLSID_ApplicationView);
	if (FAILED(HR))
	{
		return;
	}

	//We can use all the normal OpenGL API defined in the standard Opengl header file
	const float radius = 0.34f;

	ApplicationView->InitializeEnvironment(TRUE);
	ApplicationView->BeginGraphicsCommands();

	//Set the Background Color
	ApplicationView->SetBkgColor(GetRValue(m_ObjectPattern.m_Color) / (float)255, GetGValue(m_ObjectPattern.m_Color) / (float)255,
		GetBValue(m_ObjectPattern.m_Color) / (float)255, 1);

	HR = ApplicationView->StartNewDisplayList();
	if (HR == E_FAIL)
	{
		return;
	}

	//Draw using Native IOpenGLView Interface
	CComPtr<IOpenGLView> OpenGLView;
	HR = OpenGLView.CoCreateInstance(CLSID_OpenGLView);
	if (FAILED(HR))
	{
		return;
	}

	OpenGLView->glTranslatef(0.01f, 0.f, 0.01f);
	OpenGLView->glColor3f(0.0f, 0.4f, 0.8f);
	OpenGLView->glBegin(GL_TRIANGLES);
		OpenGLView->glVertex3f(0.f, 0.f, 0.001f);
		OpenGLView->glVertex3f(0.f, -0.5f, 1.f);
		OpenGLView->glVertex3f(0.f, 1.f, 0.001f);
	OpenGLView->glEnd();
	OpenGLView->glColor3f(0.0f, 0.3f, 0.7f);
	OpenGLView->glBegin(GL_TRIANGLE_STRIP);
		OpenGLView->glVertex3f(1.f, -0.5f, 0.f);
		OpenGLView->glVertex3f(0.f, 0.f, 0.2f);
		OpenGLView->glVertex3f(0.f, 2.f, 0.f);
		OpenGLView->glVertex3f(-1.f, -0.5f, 0.f);
	OpenGLView->glEnd();
	
	ApplicationView->EndNewDisplayList();
	ApplicationView->EndGraphicsCommands();
	ApplicationView->Refresh();
}

void CObjectDemoExperiment::StartSimulation(BSTR ExperimentGroup, BSTR ExperimentName)
{

	if (CString(ExperimentGroup) == OBJECT_3D_TREE_ROOT_TITLE && CString(ExperimentName) == OBJECT_3D_TREE_LEAF_PATTERN_TITLE)
	{
		StartObjectSimulation();
	}
	else
	{

	}
}

void CObjectDemoExperiment::StartObjectSimulation()
{
	//AfxMessageBox(_T("CPlusTwoPhysicsExperiment::StartObjectSimulation()"));
	m_pManager->SetSimulationStatus(TRUE);
	CComPtr<IApplicationView> ApplicationView;
	HRESULT HR = ApplicationView.CoCreateInstance(CLSID_ApplicationView);
	if (FAILED(HR))
	{
		return;
	}
	float Angle = (float)0.0, x= (float)0.0, y= (float)0.0,z= (float)0.0;
	int i = 0; //Indicate Random Movment after each iteration
	while (m_pManager->m_bSimulationActive)
	{
		ApplicationView->BeginGraphicsCommands();

		if (m_ObjectPattern.m_strSimulationPattern == OBJECT_PATTERN_TYPE_ROTATE)
		{
			//Rotate the object with respect to Y Axis
			x = (float)0.1, y = (float)1.0, z = (float)0.1;
			
		}
		else if (m_ObjectPattern.m_strSimulationPattern == OBJECT_PATTERN_TYPE_RANDOM)
		{
			//Simulate Random Rotation
			switch (i)
			{
			case 0:
				x = (float)1.0, y = (float)0.1, z = (float)0.1;
				
				break;
			case 1:
				x = (float)0.1, y = (float)1.0, z = (float)0.1;
				
				break;
			case 2:
				x = (float)0.1, y = (float)0.1, z = (float)1.0;
				
				break;

			}
			i = rand() % 3;
		}
		
		if (!m_pManager->m_b3DMode)
		{
			//Set the x y Rotation point to zero for two d view
			x = 0;
			y = 0;
		}
		//Rotate the Object with the specified angle
		ApplicationView->RotateObject(Angle, x, y, z);
		ApplicationView->EndGraphicsCommands();
		ApplicationView->Refresh();
		//Process the Results
		OnNextSimulationPoint(Angle, x, y, z);

		Angle = Angle + 5;
		if (Angle > 360)
		{
			Angle = 0;
		}
		Sleep(m_ObjectPattern.m_lSimulationInterval); //Sleep for 500 Milli seconds
	}
}




void CObjectDemoExperiment::OnNextSimulationPoint(float Angle, float x, float y, float z)
{
	CString strStatus;
	strStatus.Format(_T("Simulation Points (Angle:%.3f,X:%.3f,Y:%.3f,Z:%.3f)\n"), Angle,x,y,z);

	if (m_pManager->m_bShowExperimentalParamaters)
	{
		m_pManager->AddOperationStatus(strStatus);
	}

	if (m_pManager->m_bLogSimulationResultsToCSVFile)
	{
		CString strLog;
		strLog.Format(_T("%.3f,%.3f,%.3f,%.3f\n"), Angle, x, y, z);
		m_pManager->LogSimulationPoint(strLog);
	}

	if (m_pManager->m_bDisplayRealTimeGraph)
	{
		PlotSimulationPoint(Angle,x,y,z);
	}
}

void CObjectDemoExperiment::PlotSimulationPoint(float Angle, float x, float y, float z)
{
	CGraphPoints* pPoint = new CGraphPoints();
	pPoint->m_Angle = Angle;
	pPoint->m_x = x;
	pPoint->m_y = y;
	pPoint->m_z = z;

	m_PlotInfoArray.Add(pPoint);

	CString strStatus;
	strStatus.Format(_T("Plot Data Points Count =%d"), m_PlotInfoArray.GetCount());
	m_pManager->SetStatusBarMessage(strStatus);

	DisplayObjectDemoGraph();

}


void CObjectDemoExperiment::InitializeSimulationGraph(CString ExperimentName)
{
	
	for (int i = 0; i < m_PlotInfoArray.GetCount(); i++)
	{
		CGraphPoints* pPoint = (CGraphPoints*)m_PlotInfoArray.GetAt(i);
		delete pPoint;
	}
	m_PlotInfoArray.RemoveAll();

	CComPtr<IApplicationChart> ApplicationChart;
	HRESULT HR = ApplicationChart.CoCreateInstance(CLSID_ApplicationChart);
	if (SUCCEEDED(HR))
	{
		ApplicationChart->DeleteAllCharts();
		ApplicationChart->Initialize2dChart(3);

		ApplicationChart->Set2dGraphInfo(0, _T("Angle Vs X"), _T("Angle(Degree)"), _T("X"), TRUE);
		ApplicationChart->Set2dAxisRange(0, EAxisPos::BottomAxis, 0, 365);
		ApplicationChart->Set2dAxisRange(0, EAxisPos::LeftAxis, 0, 2);

		ApplicationChart->Set2dGraphInfo(1, _T("Angle Vs Y"), _T("Angle(Degree)"), _T("Y"), TRUE);
		ApplicationChart->Set2dAxisRange(1, EAxisPos::BottomAxis, 0, 365);
		ApplicationChart->Set2dAxisRange(1, EAxisPos::LeftAxis, 0, 2);

		ApplicationChart->Set2dGraphInfo(2, _T("Angle Vs Z"), _T("Angle(Degree)"), _T("Z"), TRUE);
		ApplicationChart->Set2dAxisRange(2, EAxisPos::BottomAxis, 0, 365);
		ApplicationChart->Set2dAxisRange(2, EAxisPos::LeftAxis, 0, 2);

		ApplicationChart->ResizeChartWindow();
	}

}


void CObjectDemoExperiment::DisplayObjectDemoGraph()
{
	int iArraySize = (int)m_PlotInfoArray.GetCount();

	if (iArraySize <2)
	{
		return;
	}

	COleSafeArray			saX;
	COleSafeArray			saY;
	COleSafeArray			saZ;
	
	SAFEARRAYBOUND			sabX[2];
	SAFEARRAYBOUND			sabY[2];
	SAFEARRAYBOUND			sabZ[2];
	
	sabX[0].cElements = iArraySize;// give this exact
	sabX[1].cElements = 2; //number of columns + 1 (because the first column is where we put 
										 // the row labels - ie in 1.1, 2.1, 3.1, 4,1 etc
	sabX[0].lLbound = sabX[1].lLbound = 1;

	saX.Create(VT_R8, 2, sabX);

	//
	sabY[0].cElements = iArraySize;// give this exact
	sabY[1].cElements = 2; //number of columns + 1 (because the first column is where we put 
									  // the row labels - ie in 1.1, 2.1, 3.1, 4,1 etc
	sabY[0].lLbound = sabY[1].lLbound = 1;

	saY.Create(VT_R8, 2, sabY);

	//

	sabZ[0].cElements = iArraySize;// give this exact
	sabZ[1].cElements = 2; //number of columns + 1 (because the first column is where we put 
									  // the row labels - ie in 1.1, 2.1, 3.1, 4,1 etc
	sabZ[0].lLbound = sabZ[1].lLbound = 1;

	saZ.Create(VT_R8, 2, sabZ);

	//

	long index[2] = { 0,0 }; //a 2D graph needs a 2D array as index array

	for (int i = 0; i < iArraySize; i++)
	{
		CGraphPoints* pInfo = (CGraphPoints*)m_PlotInfoArray.GetAt(i);
		index[0] = i + 1;
		index[1] = 1;
		double pValue = pInfo->m_Angle;
		saX.PutElement(index, &pValue);
		saY.PutElement(index, &pValue);
		saZ.PutElement(index, &pValue);
		
		//Now plot the other Y Value for each data
		index[1] = 2;
		pValue = pInfo->m_x; //set the X 
		saX.PutElement(index, &pValue);

		pValue = pInfo->m_y; //set the Y
		saY.PutElement(index, &pValue);

		pValue = pInfo->m_z; //set the Z
		saZ.PutElement(index, &pValue);

	}
	//Refresh Graph on Only 10th Data entry
	if (iArraySize % 5 == 0)
	{
		CComPtr<IApplicationChart> ApplicationChart;
		HRESULT HR = ApplicationChart.CoCreateInstance(CLSID_ApplicationChart);
		if (SUCCEEDED(HR))
		{
			ApplicationChart->Set2dChartData(0, saX);
			ApplicationChart->Set2dChartData(1, saY);
			ApplicationChart->Set2dChartData(2, saZ);
			
		}
		
	}
}


void CObjectDemoExperiment::DrawClock()
{
	//Draw using ApplicationView Interface
	CComPtr<IApplicationView> ApplicationView;
	HRESULT HR = ApplicationView.CoCreateInstance(CLSID_ApplicationView);
	if (FAILED(HR))
	{
		return;
	}

	ApplicationView->InitializeEnvironment(TRUE);
	ApplicationView->BeginGraphicsCommands();

	//Set the Background Color
	ApplicationView->SetBkgColor(GetRValue(m_ObjectPattern.m_Color) / (float)255, GetGValue(m_ObjectPattern.m_Color) / (float)255,
		GetBValue(m_ObjectPattern.m_Color) / (float)255, 1);

	HR = ApplicationView->StartNewDisplayList();
	if (HR == E_FAIL)
	{
		return;
	}

	float x1=0.0,  y1=0.0;

	float segments = 100;
	float radius = 1.0;

	//Drawing Clock main Circle

	ApplicationView->SetLineWidth(4);
	ApplicationView->SetColorf(1, 0, 0);
	DrawCircle(segments, radius, x1, y1);

	//Drawing Minute Line
	ApplicationView->SetColorf(1, 1, 0);
	ApplicationView->SetLineWidth(2);
	ApplicationView->BeginDraw(GL_LINES);
		ApplicationView->Set2DVertexf(x1, y1);
		ApplicationView->Set2DVertexf(x1, (float)((radius / 3.0)*2.0));
	ApplicationView->EndDraw();

	//Drawing Hour Line
	ApplicationView->SetColorf(1, 0, 0);
	ApplicationView->SetLineWidth(2);
	ApplicationView->BeginDraw(GL_LINES);
		ApplicationView->Set2DVertexf(x1, y1);
		ApplicationView->Set2DVertexf((float)(radius / 3.0), (float)(radius / 3.0));
	ApplicationView->EndDraw();

	ApplicationView->EndNewDisplayList();
	ApplicationView->EndGraphicsCommands();
	ApplicationView->Refresh();
}

void CObjectDemoExperiment::DrawCircle(float segments, float radius, float sx, float sy)
{
	CComPtr<IOpenGLView> OpenGLView;
	HRESULT HR = OpenGLView.CoCreateInstance(CLSID_OpenGLView);
	if (FAILED(HR))
	{
		return;
	}

	OpenGLView->glBegin(GL_LINE_LOOP);
	for (int i = 0; i<segments; i++)
	{
		float theta = (float)(2.0*3.142*float(i) / float(segments)); //get the current angle
		float x = (float)(radius*cos(theta));
		float y = (float)(radius*sin(theta));
		OpenGLView->glVertex2f(x + sx, y + sy);
	}
	OpenGLView->glEnd();
}
