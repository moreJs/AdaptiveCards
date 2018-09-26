#include "pch.h"
#include "ParseUtil.h"
#include "SubmitAction.h"

using namespace AdaptiveSharedNamespace;

SubmitAction::SubmitAction() : BaseActionElement(ActionType::Submit)
{
    PopulateKnownPropertiesSet();
}

std::string SubmitAction::GetDataJson() const
{
    if(m_dataJson.empty())
    {
        return "";
    }
    else
    {
        return m_dataJson.toStyledString();
    }
}

Json::Value SubmitAction::GetDataJsonAsValue() const
{
    return m_dataJson;
}

void SubmitAction::SetDataJson(const Json::Value &value)
{
    m_dataJson = value;
}

Json::Value SubmitAction::SerializeToJsonValue() const
{
    Json::Value root = BaseActionElement::SerializeToJsonValue();

    if (!m_dataJson.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Data)] = m_dataJson;
    }

    return root;
}


std::shared_ptr<BaseActionElement> SubmitActionParser::Deserialize(
    std::shared_ptr<ElementParserRegistration>,
    std::shared_ptr<ActionParserRegistration>,
    std::vector<std::shared_ptr<AdaptiveCardParseWarning>>&,
    const Json::Value& json)
{
    std::shared_ptr<SubmitAction> submitAction = BaseActionElement::Deserialize<SubmitAction>(json);

    submitAction->SetDataJson(ParseUtil::ExtractJsonValue(json, AdaptiveCardSchemaKey::Data));

    return submitAction;
}

std::shared_ptr<BaseActionElement> SubmitActionParser::DeserializeFromString(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
    const std::string& jsonString)
{
    return SubmitActionParser::Deserialize(elementParserRegistration, actionParserRegistration, warnings, ParseUtil::GetJsonValueFromString(jsonString));
}

void SubmitAction::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Data)});
}
