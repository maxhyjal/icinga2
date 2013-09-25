/******************************************************************************
 * Icinga 2                                                                   *
 * Copyright (C) 2012-2013 Icinga Development Team (http://www.icinga.org/)   *
 *                                                                            *
 * This program is free software; you can redistribute it and/or              *
 * modify it under the terms of the GNU General Public License                *
 * as published by the Free Software Foundation; either version 2             *
 * of the License, or (at your option) any later version.                     *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program; if not, write to the Free Software Foundation     *
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.             *
 ******************************************************************************/

#ifndef SERVICEDBOBJECT_H
#define SERVICEDBOBJECT_H

#include "db_ido/dbobject.h"
#include "base/dynamicobject.h"
#include "icinga/service.h"

namespace icinga
{

/**
 * A Service database object.
 *
 * @ingroup ido
 */
class ServiceDbObject : public DbObject
{
public:
	DECLARE_PTR_TYPEDEFS(ServiceDbObject);

	ServiceDbObject(const DbType::Ptr& type, const String& name1, const String& name2);

	static void StaticInitialize(void);

	virtual Dictionary::Ptr GetConfigFields(void) const;
	virtual Dictionary::Ptr GetStatusFields(void) const;

protected:
	virtual bool IsStatusAttribute(const String& attribute) const;

	virtual void OnConfigUpdate(void);
	virtual void OnStatusUpdate(void);

private:
        static void AddCommentInternal(const Service::Ptr& service, const Dictionary::Ptr& comment, bool historical);
        static void AddCommentByType(const DynamicObject::Ptr& object, const Dictionary::Ptr& comment, bool historical);
        static void AddComments(const Service::Ptr& service);
        static void RemoveComments(const Service::Ptr& service);

        static void AddDowntimeInternal(const Service::Ptr& service, const Dictionary::Ptr& downtime, bool historical);
        static void AddDowntimeByType(const DynamicObject::Ptr& object, const Dictionary::Ptr& downtime, bool historical);
        static void AddDowntimes(const Service::Ptr& service);
        static void RemoveDowntimes(const Service::Ptr& service);

        /* Status */

	static void AddComment(const Service::Ptr& service, const Dictionary::Ptr& comment);
	static void RemoveComment(const Service::Ptr& service, const Dictionary::Ptr& comment);

	static void AddDowntime(const Service::Ptr& service, const Dictionary::Ptr& downtime);
	static void RemoveDowntime(const Service::Ptr& service, const Dictionary::Ptr& downtime);
	static void TriggerDowntime(const Service::Ptr& service, const Dictionary::Ptr& downtime);

        /* History */
        static void AddCommentHistory(const Service::Ptr& service, const Dictionary::Ptr& comment);
        static void AddDowntimeHistory(const Service::Ptr& service, const Dictionary::Ptr& downtime);
        static void AddAcknowledgementHistory(const Service::Ptr& service, const String& author, const String& comment, AcknowledgementType type, double expiry);
        static void AddNotificationHistory(const Service::Ptr& service, const std::set<User::Ptr>& users, NotificationType type, const Dictionary::Ptr& cr, const String& author, const String& text);
        static void AddStateChangeHistory(const Service::Ptr& service, const Dictionary::Ptr& cr, StateType type);

};

}

#endif /* SERVICEDBOBJECT_H */