#include "GameEventHandler.h"
#include "Hooks.h"
#include "DDNG_API.h"
#include <windows.h>
extern "C" {
bool (*PublicRegisterCPPAction)(const std::string name, const std::string description, std::function<bool(RE::Actor *)> eligibleCallback,
                                std::function<bool(RE::Actor *, std::string json_params)> executeCallback,
                                const std::string triggeringEventTypesCSV, std::string categoryStr, int priority,
                                std::string parameterSchemaJSON, std::string customCategory, std::string customParentCategory,
                                std::string tagsCSV) = nullptr;
bool (*PublicRegisterCPPSubCategory)(const std::string name, const std::string description,
                                     std::function<bool(RE::Actor *)> eligibleCallback, const std::string triggeringEventTypesCSV,
                                     int priority, std::string parameterSchemaJSON, std::string customCategory,
                                     std::string customParentCategory, std::string tagsCSV) = nullptr;
int (*PublicGetVersion)() = nullptr;
inline bool FindFunctions() {
    auto hDLL = LoadLibraryA("SkyrimNet");
    if (hDLL != nullptr) {
        PublicGetVersion = (int (*)()) GetProcAddress(hDLL, "PublicGetVersion");
        if (PublicGetVersion != nullptr && PublicGetVersion() == 2) {
            PublicRegisterCPPAction =
                (bool (*)(const std::string name, const std::string description, std::function<bool(RE::Actor *)> eligibleCallback,
                std::function<bool(RE::Actor *, std::string json_params)> executeCallback, const std::string triggeringEventTypesCSV,
                          std::string categoryStr, int priority, std::string parameterSchemaJSON, std::string customCategory,
                          std::string customParentCategory, std::string tagsCSV)) GetProcAddress(hDLL, "PublicRegisterCPPAction");
            PublicRegisterCPPSubCategory = (bool (*)(
                const std::string name, const std::string description, std::function<bool(RE::Actor *)> eligibleCallback,
                const std::string triggeringEventTypesCSV, int priority, std::string parameterSchemaJSON, std::string customCategory,
                std::string customParentCategory, std::string tagsCSV)) GetProcAddress(hDLL, "PublicRegisterCPPSubCategory");
            return true;
        }
        
    }
    return false;
}
}
namespace plugin {
    
    
    void GameEventHandler::onLoad() {
        logger::info("onLoad()");
        Hooks::install();
    }

    void GameEventHandler::onPostLoad() {
        logger::info("onPostLoad()");
    }
    bool AlwaysEligible(RE::Actor* actor) {
        if (actor->IsChild()) {
            return false;
        }
        return true;
    }
    bool ExecuteSpank(RE::Actor *,std::string) {
        logger::info("Executed Spank Action");
        return true;
    }

    std::map<std::string, std::string> keyword_to_category;
    void GameEventHandler::onPostPostLoad() {
        
        logger::info("onPostPostLoad()");
    }

    void GameEventHandler::onInputLoaded() {
        logger::info("onInputLoaded()");
    }

    void GameEventHandler::onDataLoaded() {
        logger::info("onDataLoaded()");
    }

    void GameEventHandler::onNewGame() {
        logger::info("onNewGame()");
    }

    void GameEventHandler::onPreLoadGame() {
        logger::info("onPreLoadGame()");
    }

    static bool patched = false;
    void GameEventHandler::onPostLoadGame() {
        if (patched == false) {
            if (DeviousDevicesAPI::LoadAPI()) {
                keyword_to_category.insert_or_assign("zad_DeviousBelt", "CHASTITY_BELTS");
                keyword_to_category.insert_or_assign("zad_DeviousBra", "CHASTITY_BRAS");
                keyword_to_category.insert_or_assign("zad_DeviousYoke", "YOKES");
                keyword_to_category.insert_or_assign("zad_DeviousPlug", "PLUGS");
                keyword_to_category.insert_or_assign("zad_DeviousCollar", "COLLARS");
                keyword_to_category.insert_or_assign("zad_DeviousArmCuffs", "ARM_CUFFS");
                keyword_to_category.insert_or_assign("zad_DeviousLegCuffs", "LEG_CUFFS");
                keyword_to_category.insert_or_assign("zad_DeviousGag", "GAGS");
                keyword_to_category.insert_or_assign("zad_DeviousClamps", "PIERCINGS");
                keyword_to_category.insert_or_assign("zad_DeviousPiercingsNipple", "PIERCINGS");
                keyword_to_category.insert_or_assign("zad_DeviousArmbinder", "ARMBINDERS");
                keyword_to_category.insert_or_assign("zad_DeviousBlindfold", "BLINDFOLDS");
                keyword_to_category.insert_or_assign("zad_DeviousHarness", "HARNESSES");
                keyword_to_category.insert_or_assign("zad_DeviousPlugVaginal", "PLUGS");
                keyword_to_category.insert_or_assign("zad_DeviousPlugAnal", "PLUGS");
                keyword_to_category.insert_or_assign("zad_DeviousGagPanel", "GAGS");
                keyword_to_category.insert_or_assign("zad_DeviousPiercingsVaginal", "PIERCINGS");
                keyword_to_category.insert_or_assign("zad_DeviousCorset", "CORSETS");
                keyword_to_category.insert_or_assign("zad_DeviousBoots", "BOOTS");
                keyword_to_category.insert_or_assign("zad_DeviousGloves", "GLOVES");
                keyword_to_category.insert_or_assign("zad_DeviousHood", "HOODS");
                keyword_to_category.insert_or_assign("zad_DeviousSuit", "SUITS");
                keyword_to_category.insert_or_assign("zad_DeviousButterfly", "BUTTERFLY_BINDERS");
                keyword_to_category.insert_or_assign("zad_DeviousArmbinderElbow", "ELBOW_BINDERS");
                keyword_to_category.insert_or_assign("zad_DeviousStraitJacket", "STRAITJACKETS");
                if (FindFunctions()) {
                    PublicRegisterCPPSubCategory("BDSMLOCK", "Lock a gag, collar, chastity belt, or other BDSM device on a target", AlwaysEligible, "", 1, "",
                                                 "BDSMLOCK", "", "");
                    PublicRegisterCPPSubCategory("ANKLE_SHACKLES", "Pick the ankle shackles to lock on a target", AlwaysEligible, "", 1,
                                                 "", "ANKLE_SHACKLES", "BDSMLOCK", "");
                    PublicRegisterCPPSubCategory("ARMBINDERS", "Pick the arm binder to lock on a target", AlwaysEligible, "", 1,
                                                 "", "ARMBINDERS", "BDSMLOCK", "");
                    PublicRegisterCPPSubCategory("ARM_CUFFS", "Pick the arm cuff to lock on a target", AlwaysEligible, "", 1, "",
                                                 "ARM_CUFFS", "BDSMLOCK", "");
                    PublicRegisterCPPSubCategory("CHASTITY_BELTS", "Pick the chastity belt to lock on a target", AlwaysEligible, "", 1,
                                                 "", "CHASTITY_BELTS", "BDSMLOCK", "");
                    PublicRegisterCPPSubCategory("CHASTITY_BRAS", "Pick the chastity bra to lock on a target", AlwaysEligible, "", 1,
                                                 "", "CHASTITY_BRAS", "BDSMLOCK", "");
                    PublicRegisterCPPSubCategory("BLINDFOLDS", "Pick the blindfold to lock on a target", AlwaysEligible, "", 1,
                                                 "", "BLINDFOLDS", "BDSMLOCK", "");
                    PublicRegisterCPPSubCategory("BOOTS", "Pick the boot to lock on a target", AlwaysEligible, "", 1, "", "BOOTS",
                                                 "BDSMLOCK", "");
                    PublicRegisterCPPSubCategory("BUTTERFLY_BINDERS", "Pick the butterfly binder to lock on a target", AlwaysEligible, "",
                                                 1, "", "BUTTERFLY_BINDERS", "BDSMLOCK", "");
                    PublicRegisterCPPSubCategory("COLLARS", "Pick the collar to lock on a target", AlwaysEligible, "", 1, "",
                                                 "COLLARS", "BDSMLOCK", "");
                    PublicRegisterCPPSubCategory("CORSETS", "Pick the corset to lock on a target", AlwaysEligible, "", 1, "",
                                                 "CORSETS", "BDSMLOCK", "");
                    PublicRegisterCPPSubCategory("ELBOW_BINDERS", "Pick the elbow binder to lock on a target", AlwaysEligible, "", 1,
                                                 "", "ELBOW_BINDERS", "BDSMLOCK", "");
                    PublicRegisterCPPSubCategory("GAGS", "Pick the gag to lock on a target", AlwaysEligible, "", 1, "", "GAGS",
                                                 "BDSMLOCK", "");
                    PublicRegisterCPPSubCategory("GLOVES", "Pick the glove to lock on a target", AlwaysEligible, "", 1, "",
                                                 "GLOVES", "BDSMLOCK", "");
                    PublicRegisterCPPSubCategory("HARNESSES", "Pick the harness to lock on a target", AlwaysEligible, "", 1, "",
                                                 "HARNESSES", "BDSMLOCK", "");
                    PublicRegisterCPPSubCategory("HOODS", "Pick the hood to lock on a target", AlwaysEligible, "", 1, "", "HOODS",
                                                 "BDSMLOCK", "");
                    PublicRegisterCPPSubCategory("LEG_CUFFS", "Pick the leg cuffs to lock on a target", AlwaysEligible, "", 1, "",
                                                 "LEG_CUFFS", "BDSMLOCK", "");
                    PublicRegisterCPPSubCategory("PIERCINGS", "Pick the piercing to lock on a target", AlwaysEligible, "", 1, "",
                                                 "PIERCINGS", "BDSMLOCK", "");
                    PublicRegisterCPPSubCategory("PLUGS", "Pick the plug to lock on a target", AlwaysEligible, "", 1, "", "PLUGS",
                                                 "BDSMLOCK", "");
                    PublicRegisterCPPSubCategory("SUITS", "Pick the suit to lock on a target", AlwaysEligible, "", 1, "", "SUITS",
                                                 "BDSMLOCK", "");
                    PublicRegisterCPPSubCategory("STRAITJACKETS", "Pick the straitjacket to lock on a target", AlwaysEligible, "", 1,
                                                 "", "STRAITJACKETS", "BDSMLOCK", "");
                    PublicRegisterCPPSubCategory("YOKES", "Pick the yoke to lock on a target", AlwaysEligible, "", 1, "", "YOKES",
                                                 "BDSMLOCK", "");
                    PublicRegisterCPPSubCategory("OTHER", "Pick a device outside any of the other categories to lock on a target", AlwaysEligible, "", 1, "",
                                                 "OTHER", "BDSMLOCK", "");

                    //if (auto DDE = RE::TESDataHandler::GetSingleton()->LookupLoadedModByName("Devious Devices - Expansion.esm")) {
                    for (auto armorInv: RE::TESDataHandler::GetSingleton()->GetFormArray<RE::TESObjectARMO>()) {
                        if (armorInv == nullptr) {
                            continue;
                        }
                        RE::TESObjectARMO *renderArmor = nullptr;
                        if (armorInv->HasKeywordString("zad_InventoryDevice")) {
                            renderArmor = DeviousDevicesAPI::g_API->GetDeviceRender(armorInv);
                        }
                        auto armor = renderArmor;
                        if (!armor) {
                            continue;
                        }
                        bool found = true;
                        for (auto &kc: keyword_to_category) {
                            if (armor->HasKeywordString(kc.first) || armorInv->HasKeywordString(kc.first)) {
                                std::string armorName(armorInv->GetName());
                                armorName.erase(std::remove_if(armorName.begin(), armorName.end(),
                                                               [](char c) { return !(std::isalnum(c) || std::isspace(c)); }),
                                                armorName.end());
                                std::string actionName(armorName);
                                std::replace(actionName.begin(), actionName.end(), ' ', '_');
                                std::string captured_category(kc.second);
                                auto lambda = std::function<bool(RE::Actor * actor, std::string json)>(
                                    [captured_category, armorInv](RE::Actor *actor, std::string json) {
                                        if (actor && armorInv) {
                                            auto args = RE::MakeFunctionArguments(std::move((RE::Actor *) actor),
                                                                                  std::move(RE::BSFixedString(json)),
                                                                                  std::move((RE::TESForm *) armorInv));
                                            auto engine = RE::BSScript::Internal::VirtualMachine::GetSingleton();
                                            if (!engine) {
                                                return false;
                                            }
                                            RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback = nullptr;

                                            engine->DispatchStaticCall("skynet_DeviousScript", "LockDeviceOnActor", args, callback);
                                            return true;
                                        }
                                        return false;
                                    });
                                std::string action = std::format("EQUIP_{}_{}", kc.second,actionName.c_str());
                                std::string desc = std::format("Lock a {} on a target actor", armorName);

                                PublicRegisterCPPAction(action, desc, AlwaysEligible, lambda, "", "CPP_NESTED_ACTION", 15,
                                                        "{\"target\": \"Actor\"}", captured_category, captured_category, "");
                                found = true;
                            }
                        }
                        if (found == false) {
                            std::string armorName(armorInv->GetName());
                            armorName.erase(std::remove_if(armorName.begin(), armorName.end(),
                                                           [](char c) { return !(std::isalnum(c) || std::isspace(c)); }),
                                            armorName.end());
                            std::string actionName(armorName);
                            std::replace(actionName.begin(), actionName.end(), ' ', '_');
                            std::string captured_category("OTHER");
                            auto lambda = std::function<bool(RE::Actor * actor, std::string json)>(
                                [captured_category, armorInv](RE::Actor *actor, std::string json) {
                                    if (actor && armorInv) {
                                        auto args =
                                            RE::MakeFunctionArguments(std::move((RE::Actor *) actor), std::move(RE::BSFixedString(json)),
                                                                      std::move((RE::TESForm *) armorInv));
                                        auto engine = RE::BSScript::Internal::VirtualMachine::GetSingleton();
                                        if (!engine) {
                                            return false;
                                        }
                                        RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callback = nullptr;

                                        engine->DispatchStaticCall("skynet_DeviousScript", "LockDeviceOnActor", args, callback);
                                        return true;
                                    }
                                    return false;
                                });
                            std::string action = std::format("EQUIP_{}_{}", captured_category, actionName.c_str());
                            std::string desc = std::format("Lock a {} on a target actor", armorName);

                            PublicRegisterCPPAction(action, desc, AlwaysEligible, lambda, "", "CPP_NESTED_ACTION", 15, "{\"target\": \"Actor\"}",
                                                    captured_category, captured_category, "");
                            found = true;
                        }

                    }

                    //}
                    logger::info("Found SkyrimNet API");
                }
            }
        }
        patched = true;
        logger::info("onPostLoadGame()");
    }
    void GameEventHandler::onSaveGame() {
        logger::info("onSaveGame()");
    }

    void GameEventHandler::onDeleteGame() {
        logger::info("onDeleteGame()");
    }
}  // namespace plugin