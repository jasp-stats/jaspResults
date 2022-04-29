#include "jaspReport.h"


std::string jaspReport::dataToString(std::string prefix) const
{
    return convertTextToHtml(_rawText);
}

std::string jaspReport::toHtml()
{
	return "<div class=\"jaspReport" + (_report ? "Do" : "Dont") + "\">\n" + htmlTitle() + "\n<p>" + jaspHtml::sanitizeTextForHtml(_rawText) + "</p></div>";
}

Json::Value jaspReport::dataEntry(std::string & errorMessage) const
{
	Json::Value data(jaspObject::dataEntry(errorMessage));

    data["rawtext"]			= _rawText;
    data["html"]			= toHtml();
	data["title"]			= _title;
	data["name"]			= getUniqueNestedName();
    data["report"]			= _report;

	return data;
}


Json::Value jaspReport::convertToJSON() const
{
	Json::Value obj		= jaspObject::convertToJSON();
    obj["rawtext"]		= _rawText;
	obj["report"]		= _report;

	return obj;
}

void jaspReport::convertFromJSON_SetFields(Json::Value in)
{
	jaspObject::convertFromJSON_SetFields(in);

    _rawText	= in.get("rawtext",	"null").asString();
	_report		= in.get("report",	false).asBool();
}

