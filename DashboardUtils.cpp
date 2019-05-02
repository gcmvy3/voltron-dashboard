#include "DashboardUtils.h"

DashboardUtils::DashboardUtils(QObject *parent) : QObject(parent)
{

}

/*
* Reads the numerical suffix appended to the widgetID and sets it as the widgetIndex attribute.
* This allows us to find children by name when we have an arbitrary number of instances.
*/
int DashboardUtils::getWidgetIndex(QWidget* widget)
{
   QString widgetID = widget->objectName();

   if(widgetID.contains("_"))
   {
       QString indexString = widgetID.split("_").last();
       if(!indexString.isEmpty())
       {
           return indexString.toInt();
       }
   }

   return -1;
}
