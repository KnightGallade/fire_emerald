static const u32 sFieldMugshotGfx_TestNormal[] = INCBIN_U32("graphics/field_mugshots/test/normal.4bpp.lz");
static const u32 sFieldMugshotGfx_TestAlt[] = INCBIN_U32("graphics/field_mugshots/test/alt.4bpp.lz");
static const u16 sFieldMugshotPal_TestNormal[] = INCBIN_U16("graphics/field_mugshots/test/normal.gbapal");
static const u16 sFieldMugshotPal_TestAlt[] = INCBIN_U16("graphics/field_mugshots/test/alt.gbapal");

static const u32 sFieldMugshotGfx_JoshuaNormalTL[] = INCBIN_U32("graphics/field_mugshots/joshua/joshua_normal_TL.4bpp.lz");
static const u32 sFieldMugshotGfx_JoshuaNormalTR[] = INCBIN_U32("graphics/field_mugshots/joshua/joshua_normal_TR.4bpp.lz");
static const u32 sFieldMugshotGfx_JoshuaNormalBL[] = INCBIN_U32("graphics/field_mugshots/joshua/joshua_normal_BL.4bpp.lz");
static const u32 sFieldMugshotGfx_JoshuaNormalBR[] = INCBIN_U32("graphics/field_mugshots/joshua/joshua_normal_BR.4bpp.lz");
static const u16 sFieldMugshotPal_JoshuaNormal[] = INCBIN_U16("graphics/field_mugshots/joshua/joshua_normal.gbapal");

struct MugshotGfx
{
    const u32 *gfx[MUG_COUNT];
    const u16 *pal;
};

static const struct MugshotGfx sFieldMugshots[MUGSHOT_COUNT][EMOTE_COUNT] =
{
    [MUGSHOT_TEST] =
    {
        [EMOTE_NORMAL] =
        {
            .gfx = {
                sFieldMugshotGfx_TestNormal,
                sFieldMugshotGfx_TestNormal,
                sFieldMugshotGfx_TestNormal,
                sFieldMugshotGfx_TestNormal,
            },
            .pal = sFieldMugshotPal_TestNormal,
        },

        [EMOTE_ALT] =
        {
            .gfx = {
                sFieldMugshotGfx_TestAlt,
                sFieldMugshotGfx_TestAlt,
                sFieldMugshotGfx_TestAlt,
                sFieldMugshotGfx_TestAlt,
            },
            .pal = sFieldMugshotPal_TestAlt,
        },
    },
    [MUGSHOT_JOSHUA] =
    {
        [EMOTE_NORMAL] =
        {
            .gfx = {
                sFieldMugshotGfx_JoshuaNormalTL,
                sFieldMugshotGfx_JoshuaNormalTR,
                sFieldMugshotGfx_JoshuaNormalBL,
                sFieldMugshotGfx_JoshuaNormalBR,
            },
            .pal = sFieldMugshotPal_JoshuaNormal,
        },

        [EMOTE_ALT] =
        {
            .gfx = {
                sFieldMugshotGfx_JoshuaNormalTL,
                sFieldMugshotGfx_JoshuaNormalTR,
                sFieldMugshotGfx_JoshuaNormalBL,
                sFieldMugshotGfx_JoshuaNormalBR,
            },
            .pal = sFieldMugshotPal_JoshuaNormal,
        },
    },
};