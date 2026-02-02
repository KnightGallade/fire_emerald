#ifndef GUARD_FIELD_MUGSHOTS_H
#define GUARD_FIELD_MUGSHOTS_H

void _CreateFieldMugshot(u32 id, u32 emote);
void RemoveFieldMugshot(void);
u8 GetFieldMugshotSpriteId(u8 mug);
u8 IsFieldMugshotActive(void);
void SetFieldMugshotSpriteId(u32 value);

enum {
    MUG_TL = 0,
    MUG_TR,
    MUG_BL,
    MUG_BR,
    MUG_COUNT
};

#endif // GUARD_FIELD_MUGSHOTS_H