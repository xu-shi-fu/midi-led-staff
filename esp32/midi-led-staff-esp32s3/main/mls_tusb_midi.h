// tusb_midi.h

#ifndef __tusb_midi_h__
#define __tusb_midi_h__

#include "mls_common.h"
#include "mls_module.h"

typedef struct
{
    uint8_t channel;
    uint8_t note;
    uint8_t velocity; //  velocity = 0 表示 note_off

    uint8_t revision1;
    uint8_t revision2;

    uint8_t led; // 映射到 LED 的 index

} MidiKeyState;

typedef struct mls_tusb_midi_module_t
{

    mls_module module;

} mls_tusb_midi_module;

////////////////////////////////////////////////////////////////////////////////

mls_module *mls_tusb_midi_module_init(mls_tusb_midi_module *m1);

// void mls_midi_init();
// void mls_midi_loop();

MidiKeyState *mls_midi_get_key_state_buffer(uint *out_count);
MidiKeyState *mls_midi_get_key_state_cell(uint index);

#endif // __tusb_midi_h__
