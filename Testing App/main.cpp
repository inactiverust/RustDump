#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "utils.hpp"

namespace Offsets {
    //GOM
    uint64_t GameObjectManager;
    //Script Vars
    uint64_t BaseNetworkable;
    uint64_t GraphicsConvar;
    uint64_t ConsoleTypeInfo;
    uint64_t OcclusionCulling;
    uint64_t Client;
    uint64_t Sky;
    uint64_t Admin;
};
class VarOffset {
public:
    std::string className; // Name of Class the Variable is an attribute of
    std::string varName; // Name of Variable in Output
    std::string searchParam; // Name of Variable to Search
    std::string offsetStr; // Offset e.g 0x224
    std::string comment; //Use Second Constructor if You want to Add comments
    //Constructor
    VarOffset(std::string varName, std::string searchParam, std::string className) {
        this->varName = varName;
        this->searchParam = searchParam;
        this->className = className;
    }
    VarOffset(std::string varName, std::string searchParam, std::string className, std::string comment) {
        this->varName = varName;
        this->searchParam = searchParam;
        this->className = className;
        this->comment = comment;
    }
};

std::vector<std::string> fileLines;
//Initialization of All of the Offsets to be Scanned
//Check Out VarOffset Class to see How It is Used
std::vector<VarOffset> offsetList =
{
VarOffset("oAllowRunFromServer", "public bool AllowRunFromServer; // ", "public class ConsoleSystem.Command", "\n"),
VarOffset("oPlayerFlags", "public BasePlayer.PlayerFlags playerFlags; // ", "public class BasePlayer : BaseCombatEntity", "BasePlayer"),
VarOffset("oPlayerName", "protected string _displayName; // ", "public class BasePlayer : BaseCombatEntity"),
VarOffset("oLastSentTickTime", "private float lastSentTickTime; // ", "public class BasePlayer : BaseCombatEntity"),
VarOffset("oClientTeam", "public PlayerTeam clientTeam; // ", "public class BasePlayer : BaseCombatEntity"),
VarOffset("oSteamID", "public ulong userID; // ", "public class BasePlayer : BaseCombatEntity"),
VarOffset("oPlayerInventory", "public PlayerInventory inventory; // ", "public class BasePlayer : BaseCombatEntity"),
VarOffset("oPlayerEyes", "public PlayerEyes eyes; // ", "public class BasePlayer : BaseCombatEntity"),
VarOffset("oActiveUID", "private uint clActiveItem; // ", "public class BasePlayer : BaseCombatEntity"),
VarOffset("oFrozen", "public bool Frozen; // ", "public class BasePlayer : BaseCombatEntity"),
VarOffset("oWaterBonus", "public float clothingWaterSpeedBonus; // ", "public class BasePlayer : BaseCombatEntity"),
VarOffset("oNoBlockAiming", "public bool clothingBlocksAiming; // ", "public class BasePlayer : BaseCombatEntity"),
VarOffset("oSpeedReduction", "public float clothingMoveSpeedReduction; // ", "public class BasePlayer : BaseCombatEntity"),
VarOffset("oClothingAccuracyBonus", "public float clothingAccuracyBonus; // ", "public class BasePlayer : BaseCombatEntity", "\n"),
VarOffset("oPlayerHealth", "protected float _health; // ", "public class BaseCombatEntity : BaseEntity", "BaseCombatEntity\n"),
VarOffset("oSuccessFraction", "public float successFraction; // ", "public class FlintStrikeWeapon : BaseProjectile"),
VarOffset("oAttackRadius", "public float attackRadius; // ", "public class BaseMelee : AttackEntity"),
VarOffset("oIsAutomatic", "public bool isAutomatic; // ", "public class BaseMelee : AttackEntity"),
VarOffset("oEffectiveRange", "public float effectiveRange; // ", "public class AttackEntity : HeldEntity"),
VarOffset("oMaxDistance", "public float maxDistance; // ", "public class BaseMelee : AttackEntity"),
VarOffset("oRepeatDelay", "public float repeatDelay; // ", "public class AttackEntity : HeldEntity"),
VarOffset("oDisplayName", "public Translate.Phrase displayName; // ", "public class ItemDefinition : MonoBehaviour"),
VarOffset("oAimconePenaltyPerShot", "public float aimconePenaltyPerShot; // ", "public class BaseProjectile : AttackEntity"),
VarOffset("oStancePenalty", "private float stancePenalty; // ", "public class BaseProjectile : AttackEntity"),
VarOffset("oAimconePenalty", "private float aimconePenalty; // ", "public class BaseProjectile : AttackEntity"),
VarOffset("oHipAimCone", "public float hipAimCone; // ", "public class BaseProjectile : AttackEntity"),
VarOffset("oAimCone", "public float aimCone; // ", "public class BaseProjectile : AttackEntity"),
VarOffset("oAuto", "public bool automatic; // ", "public class BaseProjectile : AttackEntity"),
VarOffset("oShortName", "public string shortname; // ", "public class ItemDefinition : MonoBehaviour"),
VarOffset("oCreatedProjectiles", "private List<Projectile> createdProjectiles; // ", "public class BaseProjectile : AttackEntity"),
VarOffset("oPlayerMovement", "public BaseMovement movement; // ", "public class BasePlayer : BaseCombatEntity"),
VarOffset("oGravityMultiplier", "public float gravityMultiplier; // ", "public class PlayerWalkMovement : BaseMovement"),
VarOffset("oGroundAngle", "private float groundAngle; // ", "public class PlayerWalkMovement : BaseMovement"),
VarOffset("oGroundAngleNew", "private float groundAngleNew; // ", "public class PlayerWalkMovement : BaseMovement"),
VarOffset("oRecoilProperties", "public RecoilProperties recoil; // ", "public class BaseProjectile : AttackEntity"),
VarOffset("oRecoilMinYaw", "public float recoilYawMin; // ", "public class RecoilProperties : ScriptableObject"),
VarOffset("oRecoilMaxYaw", "public float recoilYawMax; // ", "public class RecoilProperties : ScriptableObject"),
VarOffset("oRecoilMinPitch", "public float recoilPitchMin; // ", "public class RecoilProperties : ScriptableObject"),
VarOffset("oRecoilMaxPitch", "public float recoilPitchMax; // ", "public class RecoilProperties : ScriptableObject"),
VarOffset("oPlayerModel", "public PlayerModel playerModel; // ", "public class BasePlayer : BaseCombatEntity"),
VarOffset("oVisible", "internal bool visible; // ", "public class PlayerModel : ListComponent<PlayerModel>"),
VarOffset("oPlayerInput", "public PlayerInput input; // ", "public class BasePlayer : BaseCombatEntity"),
VarOffset("oBodyAngles", "private Vector3 bodyAngles; // ", "public class PlayerInput : EntityComponent<BasePlayer>"),
VarOffset("oRecoilAngles", "public Vector3 recoilAngles; // ", "public class PlayerInput : EntityComponent<BasePlayer>"),
VarOffset("oHasKeyFocus", "private bool hasKeyFocus; // ", "public class PlayerInput : EntityComponent<BasePlayer>"),
VarOffset("oLifestate", "public BaseCombatEntity.LifeState lifestate; // ", "public class BaseCombatEntity : BaseEntity"),
VarOffset("oHeld", "private EntityRef heldEntity; // ", "public class Item //")
};
// Scans Script.json file for values
void getConVars() {
    std::ifstream t("script.json");
    std::stringstream buffer;
    buffer << t.rdbuf();
    if (buffer.str().size() == 0) {
        std::cout << "Script.JSON Error File May Be Missing";
        return;
    }
    Offsets::BaseNetworkable = std::stoi(Utils::findAddress(buffer.str(), "BaseNetworkable_c"));
    Offsets::GraphicsConvar = std::stoi(Utils::findAddress(buffer.str(), "ConVar_Graphics_c"));
    Offsets::ConsoleTypeInfo = std::stoi(Utils::findAddress(buffer.str(), "ConsoleSystem_Index_c"));
    Offsets::OcclusionCulling = std::stoi(Utils::findAddress(buffer.str(), "OcclusionCulling_c*"));
    Offsets::Client = std::stoi(Utils::findAddress(buffer.str(), "ConVar_Client_c*"));
    Offsets::Sky = std::stoi(Utils::findAddress(buffer.str(), "TOD_Sky_c*"));
    Offsets::Admin = std::stoi(Utils::findAddress(buffer.str(), "ConVar_Admin_c*"));
}
// Sig Scans for GOM offset
void getGOM() {
    //50 ? ? ? ? ? ? ? 7C 0D ? ?  ? ? ? ? 80 0D
    std::vector<uint8_t> mask{ 80, 00, 00, 00, 00, 00, 00, 00, 124, 13, 00, 00, 00, 00, 00, 00, 128, 13 };
    Offsets::GameObjectManager = Utils::sigScan(mask);
}
//Scans Dump.CS for class index then scans for the next occurence of the offset string
void getVarOffset(VarOffset *inputOffset) {
    std::string returnStr = "";
    std::ifstream t("dump.cs");
    std::stringstream buffer;
    buffer << t.rdbuf();
    if (buffer.str().size() == 0) {
        std::cout << "Dump.CS Error File May Be Missing";
    }
    int classIndex = buffer.str().find(inputOffset->className, 0);
    for (int i = buffer.str().find(inputOffset->searchParam, classIndex) + inputOffset->searchParam.size(); buffer.str().size(); i++) {
        if (buffer.str().at(i) == '\n') {
            break;
        }
        else {
            returnStr = returnStr + buffer.str().at(i);
        }
    }
    inputOffset->offsetStr = returnStr;
}
//Fills the fileLines list
void fillFileLines() {
    //Add Any Lines Like Gun IDs or Things That Don't Change Before Here
    fileLines.push_back("#define oGameObjectManager " + std::to_string(Offsets::GameObjectManager));
    fileLines.push_back("#define oBaseNetworkable " + std::to_string(Offsets::BaseNetworkable));
    fileLines.push_back("#define oGraphics " + std::to_string(Offsets::GraphicsConvar));
    fileLines.push_back("#define oConsoleTypeInfo " + std::to_string(Offsets::ConsoleTypeInfo));
    fileLines.push_back("#define oOcclusionCulling " + std::to_string(Offsets::OcclusionCulling));
    fileLines.push_back("#define oClient " + std::to_string(Offsets::Client));
    fileLines.push_back("#define oSky " + std::to_string(Offsets::Sky));  
    fileLines.push_back("#define oAdminConVar " + std::to_string(Offsets::Admin));
    fileLines.push_back(""); //padding
    for (int i = 0; i < offsetList.size(); i++) {
        fileLines.push_back("#define " + offsetList.at(i).varName + " " + offsetList.at(i).offsetStr + " //" + offsetList.at(i).comment);
    }
}
int main()
{
    //Calls the getvaroffset for every object in the list
    for (int i = 0; i < offsetList.size(); i++) {
        getVarOffset(&offsetList.at(i));
    }
    getConVars();
    getGOM();
    fillFileLines();
    Utils::strArrToFile(fileLines);
    std::cout << "Done!";
    for (;;) {
        Sleep(1);
    }
}