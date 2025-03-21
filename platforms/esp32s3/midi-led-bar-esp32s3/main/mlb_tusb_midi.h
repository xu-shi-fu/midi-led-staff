// tusb_midi.h

#ifndef __tusb_midi_h__
#define __tusb_midi_h__

#include "mlb_common.h"

typedef struct
{
    uint8_t channel;
    uint8_t note;
    uint8_t velocity; //  velocity = 0 表示 note_off

    uint8_t revision1;
    uint8_t revision2;

    uint8_t led; // 映射到 LED 的 index

} MidiKeyState;

void mlb_midi_init();
void mlb_midi_loop();

MidiKeyState *mlb_midi_get_key_state_buffer(uint *out_count);
MidiKeyState *mlb_midi_get_key_state_cell(uint index);

#endif // __tusb_midi_h__
