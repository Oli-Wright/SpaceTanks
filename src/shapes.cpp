// 3D shapes used in Space Tanks, a homage to Battlezone
//
// The data in this file are derived from the Battlezone Disassembly project
// by Andy McFadden https://6502disassembly.com/va-battlezone/
//
// Battlezone is Copyright 1980 Atari, Inc
//     By Ed Rotberg, Jed Margolin, Harry Jenkins, Roger Hector, Howard Delman,
//     Mike Albaugh, Dan Pliskin, Doug Snyder, Owen Rubin, and Morgan Hoff.
//
// Please see the Battlezone Dissasembly project for more information.

#include "shapes.h"
#include "picovectorscope.h"

static constexpr StandardFixedTranslationVector kPyrPoints[] =
{
    StandardFixedTranslationVector(-0.500000f, -0.625000f, -0.500000f),
    StandardFixedTranslationVector(-0.500000f, -0.625000f, 0.500000f),
    StandardFixedTranslationVector(0.500000f, -0.625000f, 0.500000f),
    StandardFixedTranslationVector(0.500000f, -0.625000f, -0.500000f),
    StandardFixedTranslationVector(0.000000f, 0.625000f, 0.000000f),
};

static constexpr StandardFixedTranslationVector kBoxPoints[] =
{
    StandardFixedTranslationVector(-0.500000f, -0.625000f, -0.500000f),
    StandardFixedTranslationVector(-0.500000f, -0.625000f, 0.500000f),
    StandardFixedTranslationVector(0.500000f, -0.625000f, 0.500000f),
    StandardFixedTranslationVector(0.500000f, -0.625000f, -0.500000f),
    StandardFixedTranslationVector(-0.500000f, 0.625000f, -0.500000f),
    StandardFixedTranslationVector(-0.500000f, 0.625000f, 0.500000f),
    StandardFixedTranslationVector(0.500000f, 0.625000f, 0.500000f),
    StandardFixedTranslationVector(0.500000f, 0.625000f, -0.500000f),
};

static constexpr StandardFixedTranslationVector kTank1Points[] =
{
    StandardFixedTranslationVector(-0.718750f, -0.625000f, -0.500000f),
    StandardFixedTranslationVector(-0.718750f, -0.625000f, 0.500000f),
    StandardFixedTranslationVector(0.945312f, -0.625000f, 0.500000f),
    StandardFixedTranslationVector(0.945312f, -0.625000f, -0.500000f),
    StandardFixedTranslationVector(-1.000000f, -0.406250f, -0.554688f),
    StandardFixedTranslationVector(-1.000000f, -0.406250f, 0.554688f),
    StandardFixedTranslationVector(1.218750f, -0.406250f, 0.554688f),
    StandardFixedTranslationVector(1.218750f, -0.406250f, -0.554688f),
    StandardFixedTranslationVector(-0.664062f, -0.234375f, -0.335938f),
    StandardFixedTranslationVector(-0.664062f, -0.234375f, 0.335938f),
    StandardFixedTranslationVector(0.664062f, -0.234375f, 0.335938f),
    StandardFixedTranslationVector(0.664062f, -0.234375f, -0.335938f),
    StandardFixedTranslationVector(-0.500000f, 0.093750f, -0.164062f),
    StandardFixedTranslationVector(-0.500000f, 0.093750f, 0.164062f),
    StandardFixedTranslationVector(-0.125000f, -0.015625f, -0.039062f),
    StandardFixedTranslationVector(-0.125000f, -0.015625f, 0.039062f),
    StandardFixedTranslationVector(0.125000f, -0.093750f, 0.039062f),
    StandardFixedTranslationVector(0.125000f, -0.093750f, -0.039062f),
    StandardFixedTranslationVector(1.093750f, -0.015625f, 0.039062f),
    StandardFixedTranslationVector(1.093750f, -0.093750f, 0.039062f),
    StandardFixedTranslationVector(1.093750f, -0.015625f, -0.039062f),
    StandardFixedTranslationVector(1.093750f, -0.093750f, -0.039062f),
    StandardFixedTranslationVector(-0.500000f, 0.093750f, 0.000000f),
    StandardFixedTranslationVector(-0.500000f, 0.156250f, 0.000000f),
};

static constexpr StandardFixedTranslationVector kTank2Points[] =
{
    StandardFixedTranslationVector(1.421875f, -0.625000f, 0.359375f),
    StandardFixedTranslationVector(-0.445312f, -0.625000f, 0.539062f),
    StandardFixedTranslationVector(-0.445312f, -0.625000f, -0.539062f),
    StandardFixedTranslationVector(1.421875f, -0.625000f, -0.359375f),
    StandardFixedTranslationVector(-0.445312f, -0.179688f, 0.445312f),
    StandardFixedTranslationVector(-0.445312f, -0.179688f, -0.445312f),
    StandardFixedTranslationVector(1.070312f, -0.539062f, 0.000000f),
    StandardFixedTranslationVector(-0.265625f, -0.226562f, 0.265625f),
    StandardFixedTranslationVector(-0.445312f, -0.179688f, 0.265625f),
    StandardFixedTranslationVector(-0.445312f, -0.179688f, -0.265625f),
    StandardFixedTranslationVector(-0.265625f, -0.226562f, -0.265625f),
    StandardFixedTranslationVector(-0.265625f, 0.085938f, 0.179688f),
    StandardFixedTranslationVector(-0.445312f, 0.085938f, 0.179688f),
    StandardFixedTranslationVector(-0.445312f, 0.085938f, -0.179688f),
    StandardFixedTranslationVector(-0.265625f, 0.085938f, -0.179688f),
    StandardFixedTranslationVector(1.250000f, -0.085938f, 0.085938f),
    StandardFixedTranslationVector(0.085938f, -0.085938f, 0.085938f),
    StandardFixedTranslationVector(0.085938f, -0.085938f, -0.085938f),
    StandardFixedTranslationVector(1.250000f, -0.085938f, -0.085938f),
    StandardFixedTranslationVector(1.250000f, 0.000000f, 0.085938f),
    StandardFixedTranslationVector(-0.085938f, 0.000000f, 0.085938f),
    StandardFixedTranslationVector(-0.085938f, 0.000000f, -0.085938f),
    StandardFixedTranslationVector(1.250000f, 0.000000f, -0.085938f),
    StandardFixedTranslationVector(-0.445312f, 0.085938f, 0.000000f),
    StandardFixedTranslationVector(-0.445312f, 0.539062f, 0.000000f),
};

static constexpr StandardFixedTranslationVector kProjectilePoints[] =
{
    StandardFixedTranslationVector(-0.039062f, -0.093750f, -0.039062f),
    StandardFixedTranslationVector(-0.039062f, -0.015625f, -0.039062f),
    StandardFixedTranslationVector(-0.039062f, -0.015625f, 0.039062f),
    StandardFixedTranslationVector(-0.039062f, -0.093750f, 0.039062f),
    StandardFixedTranslationVector(0.078125f, -0.054688f, 0.000000f),
};

static constexpr StandardFixedTranslationVector kMissilePoints[] =
{
    StandardFixedTranslationVector(-0.375000f, 0.000000f, 0.140625f),
    StandardFixedTranslationVector(-0.375000f, 0.093750f, 0.070312f),
    StandardFixedTranslationVector(-0.375000f, 0.093750f, -0.070312f),
    StandardFixedTranslationVector(-0.375000f, 0.000000f, -0.140625f),
    StandardFixedTranslationVector(-0.375000f, -0.093750f, -0.070312f),
    StandardFixedTranslationVector(-0.375000f, -0.093750f, 0.070312f),
    StandardFixedTranslationVector(-0.093750f, 0.000000f, 0.281250f),
    StandardFixedTranslationVector(-0.093750f, 0.187500f, 0.187500f),
    StandardFixedTranslationVector(-0.093750f, 0.187500f, -0.187500f),
    StandardFixedTranslationVector(-0.093750f, 0.000000f, -0.281250f),
    StandardFixedTranslationVector(-0.093750f, -0.187500f, -0.187500f),
    StandardFixedTranslationVector(-0.093750f, -0.187500f, 0.187500f),
    StandardFixedTranslationVector(1.125000f, 0.000000f, 0.000000f),
    StandardFixedTranslationVector(1.359375f, 0.000000f, 0.000000f),
    StandardFixedTranslationVector(-0.140625f, -0.328125f, -0.140625f),
    StandardFixedTranslationVector(-0.140625f, -0.328125f, 0.140625f),
    StandardFixedTranslationVector(0.140625f, -0.328125f, 0.140625f),
    StandardFixedTranslationVector(0.140625f, -0.328125f, -0.140625f),
    StandardFixedTranslationVector(-0.046875f, -0.179688f, -0.046875f),
    StandardFixedTranslationVector(-0.046875f, -0.179688f, 0.046875f),
    StandardFixedTranslationVector(0.046875f, -0.164062f, 0.046875f),
    StandardFixedTranslationVector(0.046875f, -0.164062f, -0.046875f),
    StandardFixedTranslationVector(-0.093750f, 0.187500f, 0.000000f),
    StandardFixedTranslationVector(0.515625f, 0.093750f, 0.070312f),
    StandardFixedTranslationVector(0.515625f, 0.093750f, -0.070312f),
    StandardFixedTranslationVector(0.046875f, 0.281250f, 0.000000f),
};

static constexpr StandardFixedTranslationVector kSaucerPoints[] =
{
    StandardFixedTranslationVector(-0.234375f, -0.078125f, 0.000000f),
    StandardFixedTranslationVector(-0.156250f, -0.078125f, 0.156250f),
    StandardFixedTranslationVector(0.000000f, -0.078125f, 0.234375f),
    StandardFixedTranslationVector(0.156250f, -0.078125f, 0.156250f),
    StandardFixedTranslationVector(0.234375f, -0.078125f, 0.000000f),
    StandardFixedTranslationVector(0.156250f, -0.078125f, -0.156250f),
    StandardFixedTranslationVector(0.000000f, -0.078125f, -0.234375f),
    StandardFixedTranslationVector(-0.156250f, -0.078125f, -0.156250f),
    StandardFixedTranslationVector(-0.937500f, 0.156250f, 0.000000f),
    StandardFixedTranslationVector(-0.664062f, 0.156250f, 0.664062f),
    StandardFixedTranslationVector(0.000000f, 0.156250f, 0.937500f),
    StandardFixedTranslationVector(0.664062f, 0.156250f, 0.664062f),
    StandardFixedTranslationVector(0.937500f, 0.156250f, 0.000000f),
    StandardFixedTranslationVector(0.664062f, 0.156250f, -0.664062f),
    StandardFixedTranslationVector(0.000000f, 0.156250f, -0.937500f),
    StandardFixedTranslationVector(-0.664062f, 0.156250f, -0.664062f),
    StandardFixedTranslationVector(0.000000f, 0.546875f, 0.000000f),
};

static constexpr StandardFixedTranslationVector kRTread0Points[] =
{
    StandardFixedTranslationVector(-0.925781f, -0.460938f, -0.539062f),
    StandardFixedTranslationVector(-0.925781f, -0.460938f, 0.539062f),
    StandardFixedTranslationVector(-0.824219f, -0.539062f, -0.523438f),
    StandardFixedTranslationVector(-0.824219f, -0.539062f, 0.523438f),
    StandardFixedTranslationVector(-0.718750f, -0.617188f, -0.503906f),
    StandardFixedTranslationVector(-0.718750f, -0.617188f, 0.503906f),
};

static constexpr StandardFixedTranslationVector kFTread0Points[] =
{
    StandardFixedTranslationVector(1.218750f, -0.406250f, -0.554688f),
    StandardFixedTranslationVector(1.218750f, -0.406250f, 0.554688f),
    StandardFixedTranslationVector(1.125000f, -0.484375f, -0.535156f),
    StandardFixedTranslationVector(1.125000f, -0.484375f, 0.535156f),
    StandardFixedTranslationVector(1.031250f, -0.562500f, -0.519531f),
    StandardFixedTranslationVector(1.031250f, -0.562500f, 0.519531f),
};

static constexpr StandardFixedTranslationVector kRadarPoints[] =
{
    StandardFixedTranslationVector(0.000000f, 0.156250f, -0.078125f),
    StandardFixedTranslationVector(0.078125f, 0.195312f, -0.156250f),
    StandardFixedTranslationVector(0.078125f, 0.234375f, -0.156250f),
    StandardFixedTranslationVector(0.000000f, 0.273438f, -0.078125f),
    StandardFixedTranslationVector(0.000000f, 0.156250f, 0.078125f),
    StandardFixedTranslationVector(0.078125f, 0.195312f, 0.156250f),
    StandardFixedTranslationVector(0.078125f, 0.234375f, 0.156250f),
    StandardFixedTranslationVector(0.000000f, 0.273438f, 0.078125f),
};

static constexpr StandardFixedTranslationVector kChunk0Points[] =
{
    StandardFixedTranslationVector(0.214844f, -0.531250f, 0.000000f),
    StandardFixedTranslationVector(-0.312500f, -0.367188f, -0.078125f),
    StandardFixedTranslationVector(0.332031f, -0.187500f, 0.078125f),
    StandardFixedTranslationVector(-0.179688f, -0.695312f, 0.000000f),
    StandardFixedTranslationVector(-0.121094f, -0.500000f, -0.078125f),
    StandardFixedTranslationVector(-0.113281f, -0.406250f, 0.078125f),
};

static constexpr StandardFixedTranslationVector kChunk1Points[] =
{
    StandardFixedTranslationVector(-0.234375f, -0.625000f, -0.117188f),
    StandardFixedTranslationVector(-0.367188f, -0.546875f, 0.062500f),
    StandardFixedTranslationVector(0.703125f, -0.750000f, 0.156250f),
    StandardFixedTranslationVector(0.625000f, -0.625000f, -0.117188f),
    StandardFixedTranslationVector(-0.039062f, -0.156250f, -0.062500f),
    StandardFixedTranslationVector(0.000000f, -0.117188f, 0.031250f),
    StandardFixedTranslationVector(0.054688f, -0.390625f, -0.156250f),
    StandardFixedTranslationVector(0.117188f, -0.468750f, 0.195312f),
};

static constexpr StandardFixedTranslationVector kChunk2Points[] =
{
    StandardFixedTranslationVector(-0.574219f, -0.289062f, -0.335938f),
    StandardFixedTranslationVector(-0.574219f, -0.289062f, 0.335938f),
    StandardFixedTranslationVector(0.574219f, -0.953125f, 0.335938f),
    StandardFixedTranslationVector(0.574219f, -0.953125f, -0.335938f),
    StandardFixedTranslationVector(-0.265625f, -0.093750f, -0.164062f),
    StandardFixedTranslationVector(-0.265625f, -0.093750f, 0.164062f),
    StandardFixedTranslationVector(0.000000f, -0.367188f, -0.039062f),
    StandardFixedTranslationVector(0.000000f, -0.367188f, 0.039062f),
    StandardFixedTranslationVector(0.175781f, -0.562500f, 0.039062f),
    StandardFixedTranslationVector(0.175781f, -0.562500f, -0.039062f),
    StandardFixedTranslationVector(1.054688f, -0.976562f, 0.039062f),
    StandardFixedTranslationVector(1.015625f, -1.046875f, 0.039062f),
    StandardFixedTranslationVector(1.054688f, -0.976562f, -0.039062f),
    StandardFixedTranslationVector(1.015625f, -1.046875f, -0.039062f),
};

static constexpr StandardFixedTranslationVector kChunk3Points[] =
{
    StandardFixedTranslationVector(-0.292969f, -0.359375f, -0.070312f),
    StandardFixedTranslationVector(-0.226562f, -0.359375f, -0.164062f),
    StandardFixedTranslationVector(-0.226562f, -0.460938f, -0.265625f),
    StandardFixedTranslationVector(-0.292969f, -0.554688f, -0.265625f),
    StandardFixedTranslationVector(-0.093750f, -0.398438f, 0.164062f),
    StandardFixedTranslationVector(0.039062f, -0.375000f, 0.011719f),
    StandardFixedTranslationVector(0.039062f, -0.632812f, -0.253906f),
    StandardFixedTranslationVector(-0.093750f, -0.789062f, -0.226562f),
};

static constexpr StandardFixedTranslationVector kChunk4Points[] =
{
    StandardFixedTranslationVector(-0.078125f, -0.562500f, -0.011719f),
    StandardFixedTranslationVector(0.460938f, -0.843750f, 0.109375f),
    StandardFixedTranslationVector(0.781250f, 0.023438f, -0.042969f),
    StandardFixedTranslationVector(0.085938f, -0.523438f, -0.015625f),
};

static constexpr StandardFixedTranslationVector kBaPoints[] =
{
    StandardFixedTranslationVector(0.218750f, 0.062500f, 5.000000f),
    StandardFixedTranslationVector(0.218750f, 0.062500f, 3.750000f),
    StandardFixedTranslationVector(0.656250f, 0.171875f, 3.125000f),
    StandardFixedTranslationVector(1.093750f, 0.281250f, 3.437500f),
    StandardFixedTranslationVector(1.562500f, 0.390625f, 3.125000f),
    StandardFixedTranslationVector(2.000000f, 0.500000f, 3.750000f),
    StandardFixedTranslationVector(2.000000f, 0.500000f, 5.000000f),
    StandardFixedTranslationVector(0.656250f, 0.171875f, 4.375000f),
    StandardFixedTranslationVector(0.656250f, 0.171875f, 4.062500f),
    StandardFixedTranslationVector(1.093750f, 0.281250f, 4.375000f),
    StandardFixedTranslationVector(1.562500f, 0.390625f, 4.062500f),
    StandardFixedTranslationVector(1.562500f, 0.390625f, 4.375000f),
    StandardFixedTranslationVector(0.218750f, 0.062500f, 3.125000f),
    StandardFixedTranslationVector(0.031250f, 0.171875f, 2.187500f),
    StandardFixedTranslationVector(0.218750f, 0.062500f, 1.250000f),
    StandardFixedTranslationVector(2.000000f, 0.500000f, 2.187500f),
    StandardFixedTranslationVector(0.875000f, 0.218750f, 2.500000f),
    StandardFixedTranslationVector(1.000000f, 0.250000f, 2.187500f),
    StandardFixedTranslationVector(0.875000f, 0.218750f, 1.875000f),
    StandardFixedTranslationVector(1.312500f, 0.328125f, 2.187500f),
};

static constexpr StandardFixedTranslationVector kttlePoints[] =
{
    StandardFixedTranslationVector(0.218750f, 0.062500f, 0.625000f),
    StandardFixedTranslationVector(1.562500f, 0.390625f, 0.312500f),
    StandardFixedTranslationVector(1.562500f, 0.390625f, -0.625000f),
    StandardFixedTranslationVector(0.218750f, 0.062500f, -0.937500f),
    StandardFixedTranslationVector(1.562500f, 0.390625f, -1.250000f),
    StandardFixedTranslationVector(1.562500f, 0.390625f, -2.187500f),
    StandardFixedTranslationVector(0.218750f, 0.062500f, -2.187500f),
    StandardFixedTranslationVector(0.218750f, 0.062500f, -3.750000f),
    StandardFixedTranslationVector(0.437500f, 0.109375f, -5.312500f),
    StandardFixedTranslationVector(0.656250f, 0.171875f, -4.375000f),
    StandardFixedTranslationVector(0.875000f, 0.218750f, -4.375000f),
    StandardFixedTranslationVector(1.093750f, 0.281250f, -5.000000f),
    StandardFixedTranslationVector(1.312500f, 0.328125f, -4.375000f),
    StandardFixedTranslationVector(1.562500f, 0.390625f, -4.375000f),
    StandardFixedTranslationVector(1.781250f, 0.437500f, -5.312500f),
    StandardFixedTranslationVector(2.000000f, 0.500000f, -3.750000f),
    StandardFixedTranslationVector(0.656250f, 0.171875f, -2.812500f),
    StandardFixedTranslationVector(2.000000f, 0.500000f, -2.812500f),
    StandardFixedTranslationVector(2.000000f, 0.500000f, 1.875000f),
    StandardFixedTranslationVector(1.562500f, 0.390625f, 1.875000f),
    StandardFixedTranslationVector(1.562500f, 0.390625f, 0.937500f),
};

static constexpr StandardFixedTranslationVector kZonePoints[] =
{
    StandardFixedTranslationVector(-2.000000f, -0.500000f, 4.687500f),
    StandardFixedTranslationVector(-2.000000f, -0.500000f, 2.187500f),
    StandardFixedTranslationVector(-1.562500f, -0.390625f, 3.437500f),
    StandardFixedTranslationVector(-0.218750f, -0.062500f, 2.187500f),
    StandardFixedTranslationVector(-0.218750f, -0.062500f, 4.687500f),
    StandardFixedTranslationVector(-0.656250f, -0.171875f, 3.437500f),
    StandardFixedTranslationVector(-2.000000f, -0.500000f, 0.312500f),
    StandardFixedTranslationVector(-0.218750f, -0.062500f, 0.312500f),
    StandardFixedTranslationVector(-1.562500f, -0.390625f, 1.562500f),
    StandardFixedTranslationVector(-1.562500f, -0.390625f, 0.937500f),
    StandardFixedTranslationVector(-0.656250f, -0.171875f, 0.937500f),
    StandardFixedTranslationVector(-0.656250f, -0.171875f, 1.562500f),
    StandardFixedTranslationVector(-2.000000f, -0.500000f, 0.000000f),
    StandardFixedTranslationVector(-1.093750f, -0.281250f, -0.625000f),
    StandardFixedTranslationVector(-2.000000f, -0.500000f, -2.500000f),
    StandardFixedTranslationVector(-1.781250f, -0.437500f, -4.062500f),
    StandardFixedTranslationVector(-1.562500f, -0.390625f, -3.125000f),
    StandardFixedTranslationVector(-1.312500f, -0.328125f, -3.125000f),
    StandardFixedTranslationVector(-1.093750f, -0.281250f, -3.750000f),
    StandardFixedTranslationVector(-0.875000f, -0.218750f, -3.125000f),
    StandardFixedTranslationVector(-0.656250f, -0.171875f, -3.125000f),
    StandardFixedTranslationVector(-0.437500f, -0.109375f, -4.062500f),
    StandardFixedTranslationVector(-0.218750f, -0.062500f, -2.500000f),
    StandardFixedTranslationVector(-1.093750f, -0.281250f, -1.875000f),
    StandardFixedTranslationVector(-0.218750f, -0.062500f, 0.000000f),
};

static constexpr uint16_t kPyrEdges[][2] =
{
    { 0, 4 }, { 4, 1 }, { 1, 0 }, { 0, 3 }, { 3, 4 }, { 4, 2 }, { 2, 3 }, { 2, 1 },
};

static constexpr uint16_t kBoxEdges[][2] =
{
    { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 }, { 0, 4 }, { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 }, { 5, 1 }, { 2, 6 }, { 7, 3 },
};

static constexpr uint16_t kTank1Edges[][2] =
{
    { 23, 22 }, { 12, 13 }, { 14, 20 }, { 20, 18 }, { 18, 15 }, { 15, 14 }, { 14, 17 }, { 17, 16 }, { 16, 19 }, { 19, 21 }, { 21, 17 }, { 15, 16 }, { 19, 18 }, { 20, 21 }, { 3, 0 }, { 0, 4 }, { 4, 7 }, { 7, 6 }, { 6, 2 }, { 2, 3 }, { 3, 7 }, { 7, 11 }, { 11, 10 }, { 10, 6 }, { 6, 5 }, { 5, 9 }, { 9, 10 }, { 10, 13 }, { 13, 9 }, { 9, 8 }, { 8, 11 }, { 11, 12 }, { 12, 8 }, { 8, 4 }, { 4, 5 }, { 5, 1 }, { 1, 2 }, { 1, 0 },
};

static constexpr uint16_t kTank2Edges[][2] =
{
    { 0, 1 }, { 1, 4 }, { 4, 0 }, { 0, 3 }, { 3, 2 }, { 2, 5 }, { 5, 3 }, { 2, 1 }, { 4, 5 }, { 9, 10 }, { 10, 6 }, { 6, 14 }, { 14, 13 }, { 13, 9 }, { 9, 8 }, { 8, 7 }, { 7, 6 }, { 6, 11 }, { 11, 12 }, { 12, 8 }, { 12, 13 }, { 14, 11 }, { 19, 22 }, { 22, 21 }, { 21, 20 }, { 20, 16 }, { 16, 15 }, { 15, 18 }, { 18, 17 }, { 17, 16 }, { 15, 19 }, { 22, 18 }, { 17, 21 }, { 23, 24 },
};

static constexpr uint16_t kProjectileEdges[][2] =
{
    { 0, 4 }, { 4, 1 }, { 1, 0 }, { 0, 3 }, { 3, 4 }, { 4, 2 }, { 2, 3 }, { 2, 1 },
};

static constexpr uint16_t kMissileEdges[][2] =
{
    { 13, 12 }, { 12, 6 }, { 6, 0 }, { 0, 1 }, { 1, 7 }, { 7, 8 }, { 8, 9 }, { 9, 10 }, { 10, 11 }, { 11, 6 }, { 6, 7 }, { 7, 12 }, { 12, 8 }, { 8, 2 }, { 2, 3 }, { 3, 9 }, { 9, 12 }, { 12, 10 }, { 10, 4 }, { 4, 5 }, { 5, 11 }, { 11, 12 }, { 24, 23 }, { 23, 22 }, { 22, 24 }, { 24, 25 }, { 25, 23 }, { 25, 22 }, { 1, 2 }, { 3, 4 }, { 5, 0 }, { 18, 19 }, { 19, 20 }, { 20, 21 }, { 21, 18 }, { 18, 14 }, { 14, 15 }, { 15, 16 }, { 16, 17 }, { 17, 14 }, { 15, 19 }, { 20, 16 }, { 17, 21 },
};

static constexpr uint16_t kSaucerEdges[][2] =
{
    { 16, 8 }, { 8, 9 }, { 9, 16 }, { 16, 10 }, { 10, 11 }, { 11, 16 }, { 16, 12 }, { 12, 13 }, { 13, 16 }, { 16, 14 }, { 14, 15 }, { 15, 16 }, { 0, 7 }, { 7, 15 }, { 15, 8 }, { 8, 0 }, { 0, 1 }, { 1, 9 }, { 9, 10 }, { 10, 2 }, { 2, 3 }, { 3, 11 }, { 11, 12 }, { 12, 4 }, { 4, 5 }, { 5, 13 }, { 13, 14 }, { 14, 6 }, { 6, 7 }, { 6, 5 }, { 4, 3 }, { 2, 1 },
};

static constexpr uint16_t kRTread0Edges[][2] =
{
    { 0, 1 }, { 2, 3 }, { 4, 5 },
};

static constexpr uint16_t kFTread0Edges[][2] =
{
    { 0, 1 }, { 2, 3 }, { 4, 5 },
};

static constexpr uint16_t kRadarEdges[][2] =
{
    { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 }, { 0, 4 }, { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 }, { 7, 3 },
};

static constexpr uint16_t kChunk0Edges[][2] =
{
    { 0, 3 }, { 3, 5 }, { 5, 2 }, { 2, 0 }, { 0, 1 }, { 1, 2 }, { 2, 5 }, { 5, 4 }, { 4, 1 }, { 4, 3 },
};

static constexpr uint16_t kChunk1Edges[][2] =
{
    { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 }, { 0, 4 }, { 4, 6 }, { 6, 7 }, { 7, 5 }, { 5, 4 }, { 5, 1 }, { 7, 2 }, { 3, 6 },
};

static constexpr uint16_t kChunk2Edges[][2] =
{
    { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 }, { 0, 4 }, { 4, 5 }, { 5, 1 }, { 5, 2 }, { 3, 4 }, { 6, 12 }, { 12, 10 }, { 10, 7 }, { 7, 6 }, { 6, 9 }, { 9, 8 }, { 8, 11 }, { 11, 13 }, { 13, 9 }, { 7, 8 }, { 11, 10 }, { 12, 13 },
};

static constexpr uint16_t kChunk3Edges[][2] =
{
    { 1, 2 }, { 2, 3 }, { 3, 7 }, { 7, 6 }, { 6, 5 }, { 5, 4 }, { 4, 0 }, { 0, 1 }, { 1, 5 }, { 6, 2 },
};

static constexpr uint16_t kChunk4Edges[][2] =
{
    { 0, 2 }, { 2, 1 }, { 1, 3 }, { 3, 0 }, { 0, 1 }, { 2, 3 },
};

static constexpr uint16_t kBaEdges[][2] =
{
    { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 5 }, { 5, 6 }, { 6, 0 }, { 7, 8 }, { 8, 9 }, { 9, 10 }, { 10, 11 }, { 11, 7 }, { 12, 13 }, { 13, 14 }, { 14, 15 }, { 15, 12 }, { 16, 17 }, { 17, 18 }, { 18, 19 }, { 19, 16 },
};

static constexpr uint16_t kttleEdges[][2] =
{
    { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 8 }, { 8, 9 }, { 9, 10 }, { 10, 11 }, { 11, 12 }, { 12, 13 }, { 13, 14 }, { 14, 15 }, { 15, 7 }, { 7, 16 }, { 16, 17 }, { 17, 18 }, { 18, 19 }, { 19, 20 }, { 20, 0 },
};

static constexpr uint16_t kZoneEdges[][2] =
{
    { 1, 0 }, { 0, 5 }, { 5, 4 }, { 4, 3 }, { 3, 2 }, { 2, 1 }, { 1, 3 }, { 3, 7 }, { 7, 6 }, { 6, 1 }, { 9, 8 }, { 8, 11 }, { 11, 10 }, { 10, 9 }, { 14, 22 }, { 22, 23 }, { 23, 24 }, { 24, 12 }, { 12, 13 }, { 13, 14 }, { 14, 15 }, { 15, 16 }, { 16, 17 }, { 17, 18 }, { 18, 19 }, { 19, 20 }, { 20, 21 }, { 21, 22 },
};

const Shape3D kFixedShapes[(int)FixedShape::Count]
{
    SHAPE_3D(kPyrPoints, kPyrEdges),
    SHAPE_3D(kBoxPoints, kBoxEdges),
    SHAPE_3D(kTank1Points, kTank1Edges),
    SHAPE_3D(kTank2Points, kTank2Edges),
    SHAPE_3D(kProjectilePoints, kProjectileEdges),
    SHAPE_3D(kMissilePoints, kMissileEdges),
    SHAPE_3D(kSaucerPoints, kSaucerEdges),
    SHAPE_3D(kRTread0Points, kRTread0Edges),
    SHAPE_3D(kFTread0Points, kFTread0Edges),
    SHAPE_3D(kRadarPoints, kRadarEdges),
    SHAPE_3D(kChunk0Points, kChunk0Edges),
    SHAPE_3D(kChunk1Points, kChunk1Edges),
    SHAPE_3D(kChunk2Points, kChunk2Edges),
    SHAPE_3D(kChunk3Points, kChunk3Edges),
    SHAPE_3D(kChunk4Points, kChunk4Edges),
    SHAPE_3D(kBaPoints, kBaEdges),
    SHAPE_3D(kttlePoints, kttleEdges),
    SHAPE_3D(kZonePoints, kZoneEdges),
};
