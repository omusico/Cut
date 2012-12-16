
#include "MenuLMAMain.h"

#include "MenuManager.h"
#include "aced.h"

#include "StdAfx.h"

#include <afxdllx.h>
#include <rxregsvc.h>
#include <rxmfcapi.h>

#include "CAcadApplication.h"
#include "CAcadDocument.h"
#include "CAcadModelSpace.h"
#include "CAcadMenuBar.h"
#include "CAcadMenuGroup.h"
#include "CAcadMenuGroups.h"
#include "CAcadPopupMenu.h"
#include "CAcadPopupMenus.h"

#include <CommandManager.h>

#define MAIN_MENU_NAME L"管线系统"
#define MAIN_MENU_LINE_CONFIG L"管线定义"
#define MAIN_MENU_LINE_INPUT L"管线录入"
#define MAIN_MENU_LINE_CUT L"生成切面"

MenuManager* MenuManager::gMenuManager = NULL;

void MenuManager::CreateMenu(void* appId)
{
	if( gMenuManager == NULL )
	{
		gMenuManager = new MenuManager(appId);
	}
}

MenuManager* MenuManager::instance()
{
	assert(gMenuManager);

	return gMenuManager;
}

void MenuManager::unRegister()
{
	if( gMenuManager )
	{
		delete gMenuManager;
	}
}

MenuManager::MenuManager(const void* appId)
	:mAppId(appId)
{
	RegisterMenu();
}

MenuManager::~MenuManager(void)
{
	UnRegisterMenu();
}

void MenuManager::RegisterMenu()
{
	mpMainMenu = new MenuLMAMain();
	
	//注册上下文菜单
	acedAddDefaultContextMenu(mpMainMenu, mAppId, MAIN_MENU_NAME);

	//注册下拉菜单
	AddDropdownMenu();

	acutPrintf(L"菜单加载成功\n");
}

void MenuManager::UnRegisterMenu()
{
	//删除上下文菜单
	if( mpMainMenu )
	{
		acutPrintf(L"辅助系统菜单开始卸载\n");
		acedRemoveDefaultContextMenu(mpMainMenu ); // 移除默认上下文菜单
	}

	//删除主下拉菜单
	RemoveDropdownMenu();

	acutPrintf(L"菜单卸载成功\n");
}


void MenuManager::AddDropdownMenu()
{
    TRY
    {
        CAcadApplication IAcad(acedGetAcadWinApp()->GetIDispatch(TRUE));

        CAcadMenuBar IMenuBar(IAcad.get_MenuBar());

        long numberOfMenus;
        numberOfMenus = IMenuBar.get_Count();

        CAcadMenuGroups IMenuGroups(IAcad.get_MenuGroups());

        VARIANT index;
        VariantInit(&index);
        V_VT(&index) = VT_I4;
        V_I4(&index) = 0;

        CAcadMenuGroup IMenuGroup(IMenuGroups.Item(index));

        CAcadPopupMenus IPopUpMenus(IMenuGroup.get_Menus());

        CString cstrMenuName = MAIN_MENU_NAME;

        VariantInit(&index);
        V_VT(&index) = VT_BSTR;
        V_BSTR(&index) = cstrMenuName.AllocSysString();

        IDispatch* pDisp=NULL;

		//see if the menu is already there
        TRY{pDisp = IPopUpMenus.Item(index); pDisp->AddRef();} CATCH(COleDispatchException,e){}END_CATCH;

        if (pDisp==NULL) {
            //create it
            CAcadPopupMenu IPopUpMenu(IPopUpMenus.Add(cstrMenuName));

            VariantInit(&index);
            V_VT(&index) = VT_I4;
            V_I4(&index) = 0;
            IPopUpMenu.AddMenuItem(index, MAIN_MENU_LINE_CONFIG, L"_G_LMA_CONFIG");

            VariantInit(&index);
            V_VT(&index) = VT_I4;
            V_I4(&index) = 1;
            IPopUpMenu.AddSeparator(index);

            VariantInit(&index);
            V_VT(&index) = VT_I4;
            V_I4(&index) = 2;
            IPopUpMenu.AddMenuItem(index, MAIN_MENU_LINE_INPUT, CommandManager::CMD_LINE_INPUT);

			VariantInit(&index);
            V_VT(&index) = VT_I4;
            V_I4(&index) = 3;
            IPopUpMenu.AddSeparator(index);

            VariantInit(&index);
            V_VT(&index) = VT_I4;
            V_I4(&index) = 4;
            IPopUpMenu.AddMenuItem(index, MAIN_MENU_LINE_CUT,CommandManager::CMD_LIEN_CUT);

            pDisp = IPopUpMenu.m_lpDispatch;
            pDisp->AddRef();
        }

        CAcadPopupMenu IPopUpMenu(pDisp);
        if (!IPopUpMenu.get_OnMenuBar())
        {
            VariantInit(&index);
            V_VT(&index) = VT_I4;
            V_I4(&index) = numberOfMenus - 1;
            IPopUpMenu.InsertInMenuBar(index);
        }

        pDisp->Release();
    }
    CATCH(COleDispatchException,e)
    {
        e->ReportError();
        e->Delete();
    }

    END_CATCH;
}

void MenuManager::RemoveDropdownMenu()
{
	TRY
    {
        CAcadApplication IAcad(acedGetAcadWinApp()->GetIDispatch(TRUE));

        CAcadMenuBar IMenuBar(IAcad.get_MenuBar());

        CAcadMenuGroups IMenuGroups(IAcad.get_MenuGroups());

        VARIANT index;
        VariantInit(&index);
        V_VT(&index) = VT_I4;
        V_I4(&index) = 0;

        CAcadMenuGroup IMenuGroup(IMenuGroups.Item(index));

        CAcadPopupMenus IPopUpMenus(IMenuGroup.get_Menus());

        CString cstrMenuName = MAIN_MENU_NAME;

        VariantInit(&index);
        V_VT(&index) = VT_BSTR;
        V_BSTR(&index) = cstrMenuName.AllocSysString();

        IDispatch* pDisp=NULL;

		//see if the menu is already there
        TRY{pDisp = IPopUpMenus.Item(index); pDisp->AddRef();} CATCH(COleDispatchException,e){}END_CATCH;

        if (pDisp==NULL) {
            return;
        }

        CAcadPopupMenu IPopUpMenu(pDisp);
        if (IPopUpMenu.get_OnMenuBar())
		{
            VariantInit(&index);
            V_VT(&index) = VT_BSTR;
            V_BSTR(&index) = cstrMenuName.AllocSysString();
            IPopUpMenus.RemoveMenuFromMenuBar(index);
			VariantClear(&index);
        }

        pDisp->Release();
    }
    CATCH(COleDispatchException,e)
    {
        e->ReportError();
        e->Delete();
    }

    END_CATCH;
}