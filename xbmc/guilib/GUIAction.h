#pragma once
/*
 *      Copyright (C) 2005-2011 Team XBMC
 *      http://www.xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#include <vector>
#include "utils/StdString.h"

class CGUIControl;

/**
 * Class containing vector of condition->(action/navigation route) pairs and handling its execution.
 */
class CGUIAction
{
public:
  CGUIAction();
  CGUIAction(int controlID);

  /**
   * Execute actions (no navigation paths), if action is paired with condition - evaluate condition first
   */
  bool ExecuteActions(int controlID, int parentID) const;
  /**
   * Check if there is any action that meet its condition
   */
  bool HasActionsMeetingCondition() const;
  /**
   * Check if there is any action
   */
  bool HasAnyActions() const { return m_actions.size() > 0; };
  /**
   * Get navigation route that meet its conditions first
   */
  int GetNavigation() const;
  /**
   * Set navigation route
   */
  void SetNavigation(int id);

  // GetFirstAction is only needed in deprecated http api
  CStdString GetFirstAction() const { return m_actions.size() > 0 ? m_actions[0].action : ""; };
private:
  struct cond_action_pair
  {
    CStdString condition;
    CStdString action;
  };

  std::vector<cond_action_pair> m_actions;
  bool m_sendThreadMessages;

  typedef std::vector<cond_action_pair>::const_iterator ciActions;
  typedef std::vector<cond_action_pair>::iterator iActions;
  friend class CGUIControlFactory; // no need for setters / adders
};
