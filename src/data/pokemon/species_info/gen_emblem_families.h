#ifdef __INTELLISENSE__
const struct SpeciesInfo gSpeciesInfoFireEmblem[] =
{
#endif
#if P_FAMILY_MYRMIDON
    [SPECIES_MYRMIDON] =
    {
        .baseHP        = 100,
        .baseAttack    = 100,
        .baseDefense   = 100,
        .baseSpeed     = 100,
        .baseSpAttack  = 100,
        .baseSpDefense = 100,
        .types = MON_TYPES(TYPE_SWORD),
        .catchRate = 45,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 179 : 199,
        .evYield_Attack = 1,
        .evYield_Speed = 1,
        .itemRare = ITEM_QUICK_CLAW,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 35,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_PRESSURE, ABILITY_NONE, ABILITY_PICKPOCKET },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("Myrmidon"),
        .cryId = CRY_MYRMIDON,
        .natDexNum = NATIONAL_DEX_MYRMIDON,
        .categoryName = _("Sword User"),
        .height = 11,
        .weight = 340,
        .description = COMPOUND_STRING(
            "Talented swordsmen skilled in swift\n"
            "killing strokes. Equip: Swords."),
        .pokemonScale = 320,
        .pokemonOffset = 7,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Myrmidon,
        .frontPicSize = MON_COORDS_SIZE(56, 56),
        .frontPicYOffset = 4,
        .frontAnimFrames = ANIM_FRAMES(
            ANIMCMD_FRAME(1, 15),
            ANIMCMD_FRAME(0, 15),
        ),
        .frontAnimId = ANIM_H_VIBRATE,
        .backPic = gMonBackPic_Myrmidon,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 6,
        .backAnimId = BACK_ANIM_JOLT_RIGHT,
        .palette = gMonPalette_Myrmidon,
        .shinyPalette = gMonShinyPalette_Myrmidon,
        .iconSprite = gMonIcon_Myrmidon,
        .iconPalIndex = 0,
#if P_GENDER_DIFFERENCES

        .frontPicFemale = gMonFrontPic_MyrmidonF,
        .frontPicSizeFemale = MON_COORDS_SIZE(56, 56),
        .backPicFemale = gMonBackPic_MyrmidonF,
        .backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        .iconSpriteFemale = gMonIcon_MyrmidonF,
#endif //P_GENDER_DIFFERENCES
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-4, 10, SHADOW_SIZE_NONE)
        FOOTPRINT(Myrmidon)
        OVERWORLD(
            sPicTable_Myrmidon,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Myrmidon,
            gShinyOverworldPalette_Myrmidon
        )
        OVERWORLD_FEMALE(
            sPicTable_MyrmidonF,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following
        )
        .levelUpLearnset = sMyrmidonLevelUpLearnset,
        .teachableLearnset = sMyrmidonTeachableLearnset,
    },
#endif //P_FAMILY_MYRMIDON
#ifdef __INTELLISENSE__
};
#endif
