class SyberiaAdditionalHud
{
	ref Widget m_actionBlocker;
	ref TextWidget m_actionBlockerText;
	bool m_actionBlockerVisible;
	
	ref Widget m_mainHud;
	ref GridSpacerWidget m_defaultActionMenu;
	
	ref MultilineTextWidget m_screenMessageWidget;
	string m_screenMessageText;
	float m_screenMessageTimer;
	float m_screenMessageDuration;
	
	ref array<ref Widget> m_espMarkers; 
	float m_espUpdateInterval;

	void SyberiaAdditionalHud(ref Widget mainHud, ref Widget actionBlocker, ref MultilineTextWidget screenMessageWidget)
	{
		m_mainHud = mainHud;
		m_actionBlocker = actionBlocker;
		m_actionBlockerText = null;
		m_actionBlockerVisible = false;
		
		m_screenMessageWidget = screenMessageWidget;
		m_screenMessageText = "";
		m_screenMessageTimer = 0;
		m_screenMessageDuration = 0;
		
		m_espMarkers = new array<ref Widget>;
		m_espUpdateInterval = 0;
	}
	
	void ~SyberiaAdditionalHud()
	{
		if (m_espMarkers) delete m_espMarkers;
	}

	void Init()
	{
		// Init action blocker
		m_defaultActionMenu = GridSpacerWidget.Cast( m_mainHud.FindAnyWidget("ItemActions") );
		m_actionBlockerText = TextWidget.Cast( m_actionBlocker.FindAnyWidget("ia_block_interact_action_name") );
		
		// Init screen info text
		m_mainHud.AddChild(m_screenMessageWidget);
	}
	
	void Refresh(float dt)
	{
		RefreshActionBlocker(dt);
		RefreshScreenMessage(dt);
		RefreshAdminEsp(dt);
	}
	
	void RefreshActionBlocker(float dt)
	{		
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		ActionManagerBase actionManager = player.GetActionManager();
		
		int deltaBlocker = GetGame().GetTime() - actionManager.m_ActionBlockerTimeStamp;
		if (actionManager.m_ActionBlockerText.Length() > 0 && deltaBlocker < 200)
		{
			if (!m_actionBlockerVisible) {
				m_defaultActionMenu.AddChild(m_actionBlocker);
				m_actionBlockerVisible = true;
			}
			m_actionBlockerText.SetText(actionManager.m_ActionBlockerText);
		}
		else if (m_actionBlockerVisible)
		{
			m_defaultActionMenu.RemoveChild(m_actionBlocker);
			m_actionBlockerVisible = false;
		}
	}
	
	void RefreshScreenMessage(float dt)
	{
		if (m_screenMessageText.Length() > 0)
		{
			if (m_screenMessageTimer == 0)
			{
				m_screenMessageWidget.Show(true);
				m_screenMessageWidget.SetText(m_screenMessageText);
			}
			
			if (m_screenMessageTimer < 0.2)
			{
				m_screenMessageWidget.SetColor( ARGBF(m_screenMessageTimer / 0.2, 1, 1, 1) );
			}
			else if (m_screenMessageDuration - m_screenMessageTimer < 1)
			{
				m_screenMessageWidget.SetColor( ARGBF(m_screenMessageDuration - m_screenMessageTimer, 1, 1, 1) );
			}
			else
			{
				m_screenMessageWidget.SetColor( ARGBF(1, 1, 1, 1) );
			}
			
			m_screenMessageTimer = m_screenMessageTimer + dt;
			
			if (m_screenMessageTimer >= m_screenMessageDuration)
			{
				m_screenMessageDuration = 0;
				m_screenMessageText = "";
				m_screenMessageTimer = 0;
				m_screenMessageWidget.Show(false);
				m_screenMessageWidget.SetText("");
			}
		}
	}
	
	void RefreshAdminEsp(float dt)
	{
		m_espUpdateInterval = m_espUpdateInterval + dt;
		if (m_espUpdateInterval < 0.015)
			return;
		
		m_espUpdateInterval = 0;		
		PluginAdminTool adminTool = PluginAdminTool.Cast(GetPlugin(PluginAdminTool));
		if (!adminTool) return;
		if (!adminTool.HasAdminPermissions()) return;
		
		array<vector> espPoses = new array<vector>;
		array<string> espNames = new array<string>;
		array<int> espTypes = new array<int>;
		adminTool.GetEspMarkers(espPoses, espNames, espTypes);
		
		foreach (ref Widget w : m_espMarkers)
		{
			delete w;
		}
		m_espMarkers.Clear();
		
		for (int i = 0; i < espPoses.Count(); i++)
		{
			vector pos = espPoses.Get(i);
			string name = espNames.Get(i);
			int type = espTypes.Get(i);
			CreateEspMarker(pos, name, type);
		}
	}
	
	void CreateEspMarker(vector pos, string name, int type)
	{
		if (type == PluginAdminTool_EspType.PLAYER)
		{
			pos[1] = pos[1] + 1.8;
		}
		else if (type == PluginAdminTool_EspType.BODY)
		{
			pos[1] = pos[1] + 0.5;
		}
		else if (type == PluginAdminTool_EspType.VEHICLES)
		{
			pos[1] = pos[1] + 2.0;
		}
		
		int sx, sy;
		GetScreenSize(sx, sy);
		vector screenPos = GetGame().GetScreenPos(pos);
		if (screenPos[0] <= 0 || screenPos[0] >= sx) return;
		if (screenPos[1] <= 0 || screenPos[1] >= sy) return;
		if (screenPos[2] < 0) return;
		
		ref Widget w = GetGame().GetWorkspace().CreateWidgets("SyberiaScripts/layout/AdminToolMarker.layout");
		ref TextWidget tw = TextWidget.Cast(w.FindAnyWidget("Text"));
		ref ImageWidget iw = ImageWidget.Cast(w.FindAnyWidget("Image"));
		w.SetPos(screenPos[0], sy - screenPos[1]);	
		
		int color = 0;
		if (type == PluginAdminTool_EspType.PLAYER)
		{
			color = ARGB(255, 255, 0, 0);
		}
		else if (type == PluginAdminTool_EspType.BODY)
		{
			color = ARGB(255, 128, 93, 128);
			iw.LoadImageFile(0, "SyberiaScripts\\data\\gui\\Markers\\corpse.paa");
		}
		else if (type == PluginAdminTool_EspType.VEHICLES)
		{
			color = ARGB(255, 255, 216, 0);
			iw.LoadImageFile(0, "SyberiaScripts\\data\\gui\\Markers\\car.paa");
			name = GameHelpers.GetItemDisplayName(name);
		}
		else if (type == PluginAdminTool_EspType.LOOT)
		{
			color = ARGB(255, 147, 255, 0);
			name = GameHelpers.GetItemDisplayName(name);
		}
		
		tw.SetText(name);
		tw.SetColor(color);
		iw.SetColor(color);

		m_espMarkers.Insert(w);
	}
	
	void ShowScreenMessage(string message, float duration)
	{
		if (m_screenMessageText == message)
		{
			m_screenMessageTimer = 0.2;
		}
		else
		{
			m_screenMessageDuration = duration;
			m_screenMessageText = message;
			m_screenMessageTimer = 0;
		}
	}
}