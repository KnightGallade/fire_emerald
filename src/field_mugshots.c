#include "global.h"
#include "decompress.h"
#include "sprite.h"
#include "script.h"
#include "event_data.h"
#include "field_weather.h"
#include "field_message_box.h"
#include "field_mugshot.h"
#include "constants/field_mugshots.h"
#include "data/field_mugshots.h"

static EWRAM_DATA u8 sFieldMugshotSpriteIds[MUG_COUNT][2] = {};
static EWRAM_DATA u8 sIsFieldMugshotActive = 0;
static EWRAM_DATA u8 sFieldMugshotSlot = 0;

#define TAG_MUGSHOT_TL 0x9000
#define TAG_MUGSHOT_TR 0x9001
#define TAG_MUGSHOT_BL 0x9002
#define TAG_MUGSHOT_BR 0x9003
#define TAG_MUGSHOT_PAL 0x9004
#define TAG_MUGSHOT2_TL 0x9005
#define TAG_MUGSHOT2_TR 0x9006
#define TAG_MUGSHOT2_BL 0x9007
#define TAG_MUGSHOT2_BR 0x9008
#define TAG_MUGSHOT2_PAL 0x9009

// don't remove the `+ 32`
// otherwise your sprite will not be placed in the place you desire
#define MUGSHOT_X_TL 104 + 32
#define MUGSHOT_Y_TL -13  + 32 // 51 - 64
#define MUGSHOT_X_TR 168 + 32
#define MUGSHOT_Y_TR -13  + 32
#define MUGSHOT_X_BL 104 + 32
#define MUGSHOT_Y_BL 51  + 32
#define MUGSHOT_X_BR 168 + 32
#define MUGSHOT_Y_BR 51  + 32

static const s16 sMugshotPositions[MUG_COUNT][2] = {
    [MUG_TL] = { MUGSHOT_X_TL, MUGSHOT_Y_TL },
    [MUG_TR] = { MUGSHOT_X_TR, MUGSHOT_Y_TR },
    [MUG_BL] = { MUGSHOT_X_BL, MUGSHOT_Y_BL },
    [MUG_BR] = { MUGSHOT_X_BR, MUGSHOT_Y_BR },
};

static void SpriteCB_FieldMugshot(struct Sprite *s);

static const struct OamData sFieldMugshot_Oam = {
    .size = SPRITE_SIZE(64x64),
    .shape = SPRITE_SHAPE(64x64),
    .priority = 0,
};

static const struct SpriteTemplate sFieldMugshot_SpriteTemplateTL = {
    .tileTag = TAG_MUGSHOT_TL,
    .paletteTag = TAG_MUGSHOT_TL,
    .oam = &sFieldMugshot_Oam,
    .callback = SpriteCB_FieldMugshot,
    .anims = gDummySpriteAnimTable,
    .affineAnims = gDummySpriteAffineAnimTable,
};

static const struct SpriteTemplate sFieldMugshot_SpriteTemplateTR = {
    .tileTag = TAG_MUGSHOT_TR,
    .paletteTag = TAG_MUGSHOT_TR,
    .oam = &sFieldMugshot_Oam,
    .callback = SpriteCB_FieldMugshot,
    .anims = gDummySpriteAnimTable,
    .affineAnims = gDummySpriteAffineAnimTable,
};

static const struct SpriteTemplate sFieldMugshot_SpriteTemplateBL = {
    .tileTag = TAG_MUGSHOT_BL,
    .paletteTag = TAG_MUGSHOT_BL,
    .oam = &sFieldMugshot_Oam,
    .callback = SpriteCB_FieldMugshot,
    .anims = gDummySpriteAnimTable,
    .affineAnims = gDummySpriteAffineAnimTable,
};

static const struct SpriteTemplate sFieldMugshot_SpriteTemplateBR = {
    .tileTag = TAG_MUGSHOT_BR,
    .paletteTag = TAG_MUGSHOT_BR,
    .oam = &sFieldMugshot_Oam,
    .callback = SpriteCB_FieldMugshot,
    .anims = gDummySpriteAnimTable,
    .affineAnims = gDummySpriteAffineAnimTable,
};

static void SpriteCB_FieldMugshot(struct Sprite *s)
{
    if (s->data[0] == TRUE)
    {
        s->invisible = FALSE;
    }
    else
    {
        s->invisible = TRUE;
    }
}

void RemoveFieldMugshot(void)
{
    ResetPreservedPalettesInWeather();
    if (sFieldMugshotSpriteIds[MUG_TL][0] != 0xFF)
    {
        FreeSpriteTilesByTag(TAG_MUGSHOT_TL);
        FreeSpriteTilesByTag(TAG_MUGSHOT_TR);
        FreeSpriteTilesByTag(TAG_MUGSHOT_BL);
        FreeSpriteTilesByTag(TAG_MUGSHOT_BR);
        FreeSpritePaletteByTag(TAG_MUGSHOT_PAL);
        for (u8 i = 0; i < MUG_COUNT; i++)
        {
            DestroySprite(&gSprites[sFieldMugshotSpriteIds[i][0]]);
            sFieldMugshotSpriteIds[i][0] = SPRITE_NONE;
        }
    }
    if (sFieldMugshotSpriteIds[MUG_TL][1] != 0xFF)
    {
        FreeSpriteTilesByTag(TAG_MUGSHOT2_TL);
        FreeSpriteTilesByTag(TAG_MUGSHOT2_TR);
        FreeSpriteTilesByTag(TAG_MUGSHOT2_BL);
        FreeSpriteTilesByTag(TAG_MUGSHOT2_BR);
        FreeSpritePaletteByTag(TAG_MUGSHOT2_PAL);
        for (u8 i = 0; i < MUG_COUNT; i++)
        {
            DestroySprite(&gSprites[sFieldMugshotSpriteIds[i][1]]);
            sFieldMugshotSpriteIds[i][1] = SPRITE_NONE;
        }
    }
    sIsFieldMugshotActive = FALSE;
}

void CreateFieldMugshot(struct ScriptContext *ctx)
{
    u16 id = VarGet(ScriptReadHalfword(ctx));
    u16 emote = VarGet(ScriptReadHalfword(ctx));

    _CreateFieldMugshot(id, emote);
}

void _RemoveFieldMugshot(u8 slot)
{
    ResetPreservedPalettesInWeather();
    if (sFieldMugshotSpriteIds[MUG_TL][slot ^ 1] != SPRITE_NONE)
    {
        for (u8 i = 0; i < MUG_COUNT; i++)
            gSprites[sFieldMugshotSpriteIds[i][slot ^ 1]].data[0] = FALSE; // same as setting visibility
    }

    if (sFieldMugshotSpriteIds[MUG_TL][slot] != SPRITE_NONE)
    {
        for (u8 i = 0; i < MUG_COUNT; i++)
            gSprites[sFieldMugshotSpriteIds[i][slot]].data[0] = TRUE; // same as setting visibility
        FreeSpriteTilesByTag((5*slot) + TAG_MUGSHOT_TL);
        FreeSpriteTilesByTag((5*slot) + TAG_MUGSHOT_TR);
        FreeSpriteTilesByTag((5*slot) + TAG_MUGSHOT_BL);
        FreeSpriteTilesByTag((5*slot) + TAG_MUGSHOT_BR);
        FreeSpritePaletteByTag((5*slot) + TAG_MUGSHOT_PAL);
        for (u8 i = 0; i < MUG_COUNT; i++)
        {
            DestroySprite(&gSprites[sFieldMugshotSpriteIds[i][slot]]);
            sFieldMugshotSpriteIds[i][slot] = SPRITE_NONE;
        }
    }
}

void _CreateFieldMugshot(u32 id, u32 emote)
{
    u32 slot = sFieldMugshotSlot;
    struct SpriteTemplate temp[MUG_COUNT] = {sFieldMugshot_SpriteTemplateTL, sFieldMugshot_SpriteTemplateTR, sFieldMugshot_SpriteTemplateBL, sFieldMugshot_SpriteTemplateBR};
    struct CompressedSpriteSheet sheet[MUG_COUNT] = {
        { .size=0x1000, .tag=(5*slot)+TAG_MUGSHOT_TL },
        { .size=0x1000, .tag=(5*slot)+TAG_MUGSHOT_TR },
        { .size=0x1000, .tag=(5*slot)+TAG_MUGSHOT_BL },
        { .size=0x1000, .tag=(5*slot)+TAG_MUGSHOT_BR }
    };
    struct SpritePalette pal = { .tag =(5*slot)+TAG_MUGSHOT_PAL };

    DebugPrintf("id: %u, emote: %u, sFieldMugshotSlot: %u, NULL: %d", id, emote, slot, sFieldMugshots[id][emote].gfx[MUG_TL] == NULL);
    if (sIsFieldMugshotActive)
    {
        _RemoveFieldMugshot(slot);
    }

    if (id >= NELEMS(sFieldMugshots))
    {
        return;
    }

    for (u8 i = 0; i < MUG_COUNT; i++)
    {
        temp[i].tileTag = sheet[i].tag;
        temp[i].paletteTag = (slot == 0 ? TAG_MUGSHOT_PAL : TAG_MUGSHOT2_PAL);
        sheet[i].data = (sFieldMugshots[id][emote].gfx[i] != NULL ? sFieldMugshots[id][emote].gfx[i] : sFieldMugshotGfx_TestNormal);
        LoadCompressedSpriteSheet(&sheet[i]);
    }
    pal.data = (sFieldMugshots[id][emote].pal != NULL ? sFieldMugshots[id][emote].pal : sFieldMugshotPal_TestNormal);
    LoadSpritePalette(&pal);
    
    
    for (u8 i = 0; i < MUG_COUNT; i++)
    {
        sFieldMugshotSpriteIds[i][slot] = CreateSprite(&temp[i], sMugshotPositions[i][0], sMugshotPositions[i][1], 0);
        if (sFieldMugshotSpriteIds[i][slot] == SPRITE_NONE)
        {
            return;
        }
        PreservePaletteInWeather(gSprites[sFieldMugshotSpriteIds[i][slot]].oam.paletteNum + 0x10);
        gSprites[sFieldMugshotSpriteIds[i][slot]].data[0] = FALSE;
    }
    sIsFieldMugshotActive = TRUE;
    sFieldMugshotSlot ^= 1;
}

u8 GetFieldMugshotSpriteId(u8 mug)
{
    // TODO - see every time this is called, do we need a new input to check which of the 4 sprites, or do they share the id?
    return sFieldMugshotSpriteIds[mug][sFieldMugshotSlot ^ 1];
}

u8 IsFieldMugshotActive(void)
{
    return sIsFieldMugshotActive;
}

void SetFieldMugshotSpriteId(u32 value)
{
    for (u8 i = 0; i < MUG_COUNT; i++)
    {
        sFieldMugshotSpriteIds[i][0] = value;
        sFieldMugshotSpriteIds[i][1] = value;
    }
}