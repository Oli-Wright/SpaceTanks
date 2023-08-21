// Background graphics used in Space Tanks, a homage to Battlezone
//
// The data in this file are derived from the Battlezone Disassembly project
// by Andy McFadden https://6502disassembly.com/va-battlezone/
//
// Battlezone is Copyright 1980 Atari, Inc
//     By Ed Rotberg, Jed Margolin, Harry Jenkins, Roger Hector, Howard Delman,
//     Mike Albaugh, Dan Pliskin, Doug Snyder, Owen Rubin, and Morgan Hoff.
//
// Please see the Battlezone Dissasembly project for more information.

#include "background.h"
#include "spacetanks.h"

static constexpr StandardFixedTranslationVector kBackground0Points[] =
{
    StandardFixedTranslationVector(0.000000f, 6.400000f, 64.000000f),
    StandardFixedTranslationVector(3.140331f, 3.200000f, 63.922909f),
    StandardFixedTranslationVector(1.570639f, 2.400000f, 63.980724f),
    StandardFixedTranslationVector(9.390750f, 6.400000f, 63.307297f),
    StandardFixedTranslationVector(12.485781f, 6.400000f, 62.770258f),
    StandardFixedTranslationVector(15.550732f, 3.200000f, 62.082000f),
    StandardFixedTranslationVector(9.390750f, 6.400000f, 63.307297f),
    StandardFixedTranslationVector(9.390750f, 0.000000f, 63.307297f),
    StandardFixedTranslationVector(21.560951f, 6.400000f, 60.258820f),
    StandardFixedTranslationVector(27.363526f, 0.000000f, 57.855315f),
    StandardFixedTranslationVector(30.169391f, 0.000000f, 56.442961f),
    StandardFixedTranslationVector(24.491740f, 3.200000f, 59.128290f),
    StandardFixedTranslationVector(21.560951f, 6.400000f, 60.258820f),
    StandardFixedTranslationVector(27.363526f, 3.200000f, 57.855315f),
    StandardFixedTranslationVector(32.902576f, 1.600000f, 54.894631f),
    StandardFixedTranslationVector(40.601170f, 0.000000f, 49.472669f),
    StandardFixedTranslationVector(44.130595f, 16.000000f, 46.351813f),
    StandardFixedTranslationVector(44.484807f, 14.800000f, 46.011976f),
    StandardFixedTranslationVector(44.484807f, 13.600000f, 46.011976f),
    StandardFixedTranslationVector(43.916820f, 12.400000f, 46.554408f),
    StandardFixedTranslationVector(43.052465f, 11.200000f, 47.354886f),
    StandardFixedTranslationVector(42.173523f, 10.900000f, 48.139318f),
    StandardFixedTranslationVector(41.280290f, 11.200000f, 48.907439f),
    StandardFixedTranslationVector(42.173523f, 10.300000f, 48.139318f),
    StandardFixedTranslationVector(43.052465f, 10.000000f, 47.354886f),
    StandardFixedTranslationVector(43.916820f, 10.300000f, 46.554408f),
    StandardFixedTranslationVector(44.766294f, 11.200000f, 45.738156f),
    StandardFixedTranslationVector(45.185361f, 12.400000f, 45.324201f),
    StandardFixedTranslationVector(45.185361f, 13.600000f, 45.324201f),
    StandardFixedTranslationVector(44.906406f, 14.800000f, 45.600600f),
    StandardFixedTranslationVector(44.130595f, 16.000000f, 46.351813f),
    StandardFixedTranslationVector(43.197545f, 16.300000f, 47.222580f),
    StandardFixedTranslationVector(42.099628f, 15.900000f, 48.203955f),
    StandardFixedTranslationVector(41.355265f, 15.100000f, 48.844059f),
    StandardFixedTranslationVector(40.979423f, 14.000000f, 49.159810f),
    StandardFixedTranslationVector(40.828410f, 12.700000f, 49.285302f),
    StandardFixedTranslationVector(41.280290f, 11.200000f, 48.907439f),
    StandardFixedTranslationVector(43.269933f, 11.500000f, 47.156260f),
    StandardFixedTranslationVector(43.269933f, 11.100000f, 47.156260f),
    StandardFixedTranslationVector(43.702115f, 11.000000f, 46.756017f),
    StandardFixedTranslationVector(44.130595f, 12.100000f, 46.351813f),
    StandardFixedTranslationVector(43.845355f, 12.000000f, 46.621721f),
    StandardFixedTranslationVector(43.773786f, 12.200000f, 46.688924f),
    StandardFixedTranslationVector(45.046095f, 14.200000f, 45.462614f),
    StandardFixedTranslationVector(44.836403f, 13.900000f, 45.669432f),
    StandardFixedTranslationVector(44.906406f, 14.200000f, 45.600600f),
    StandardFixedTranslationVector(44.696080f, 14.300000f, 45.806773f),
    StandardFixedTranslationVector(44.696080f, 14.900000f, 45.806773f),
    StandardFixedTranslationVector(44.766294f, 15.000000f, 45.738156f),
    StandardFixedTranslationVector(45.254834f, 0.000000f, 45.254834f),
};

static constexpr uint16_t kBackground0Edges[][2] =
{
    { 0, 1 }, { 2, 3 }, { 3, 4 }, { 4, 5 }, { 5, 6 }, { 7, 8 }, { 8, 9 }, { 10, 11 }, { 12, 13 }, { 13, 14 }, { 14, 15 }, { 16, 17 }, { 17, 18 }, { 18, 19 }, { 19, 20 }, { 20, 21 }, { 21, 22 }, { 22, 23 }, { 23, 24 }, { 24, 25 }, { 25, 26 }, { 26, 27 }, { 27, 28 }, { 28, 29 }, { 29, 30 }, { 30, 31 }, { 31, 32 }, { 32, 33 }, { 33, 34 }, { 34, 35 }, { 35, 36 }, { 37, 38 }, { 38, 39 }, { 39, 40 }, { 40, 41 }, { 41, 42 }, { 43, 44 }, { 44, 45 }, { 45, 46 }, { 46, 47 }, { 47, 48 },
};

static constexpr Intensity kBackground0Intensities[] =
{
    0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 1.000000f, 0.285714f, 0.285714f, 0.285714f, 0.285714f, 0.285714f, 0.285714f, 0.714286f, 0.714286f, 0.714286f, 0.714286f, 0.714286f, 0.714286f, 0.714286f, 0.714286f, 0.714286f, 0.285714f,
};

static constexpr StandardFixedTranslationVector kBackground1Points[] =
{
    StandardFixedTranslationVector(47.420872f, 0.000000f, 42.979773f),
    StandardFixedTranslationVector(51.405282f, 4.800000f, 38.124755f),
    StandardFixedTranslationVector(53.214055f, 0.000000f, 35.556495f),
    StandardFixedTranslationVector(51.405282f, 4.800000f, 38.124755f),
    StandardFixedTranslationVector(53.214055f, 3.200000f, 35.556495f),
    StandardFixedTranslationVector(56.442961f, 6.400000f, 30.169391f),
    StandardFixedTranslationVector(62.082000f, 0.000000f, 15.550732f),
    StandardFixedTranslationVector(57.855315f, 3.200000f, 27.363526f),
    StandardFixedTranslationVector(56.442961f, 6.400000f, 30.169391f),
    StandardFixedTranslationVector(53.214055f, 3.200000f, 35.556495f),
    StandardFixedTranslationVector(57.855315f, 0.000000f, 27.363526f),
    StandardFixedTranslationVector(62.082000f, 0.000000f, 15.550732f),
    StandardFixedTranslationVector(64.000000f, 3.200000f, -0.000000f),
    StandardFixedTranslationVector(64.000000f, 0.000000f, -0.000000f),
};

static constexpr uint16_t kBackground1Edges[][2] =
{
    { 0, 1 }, { 1, 2 }, { 3, 4 }, { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 8 }, { 9, 10 }, { 11, 12 },
};

static constexpr Intensity kBackground1Intensities[] =
{
    0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f,
};

static constexpr StandardFixedTranslationVector kBackground2Points[] =
{
    StandardFixedTranslationVector(64.000000f, 3.200000f, -0.000000f),
    StandardFixedTranslationVector(63.691823f, 3.200000f, -6.273097f),
    StandardFixedTranslationVector(63.691823f, 0.000000f, -6.273097f),
    StandardFixedTranslationVector(64.000000f, 3.200000f, -0.000000f),
    StandardFixedTranslationVector(63.691823f, 3.200000f, -6.273097f),
    StandardFixedTranslationVector(62.770258f, 6.400000f, -12.485781f),
    StandardFixedTranslationVector(63.691823f, 3.200000f, -6.273097f),
    StandardFixedTranslationVector(62.082000f, 0.000000f, -15.550732f),
    StandardFixedTranslationVector(61.244181f, 3.200000f, -18.578219f),
    StandardFixedTranslationVector(62.770258f, 6.400000f, -12.485781f),
    StandardFixedTranslationVector(62.082000f, 6.400000f, -15.550732f),
    StandardFixedTranslationVector(61.244181f, 3.200000f, -18.578219f),
    StandardFixedTranslationVector(60.258820f, 4.800000f, -21.560951f),
    StandardFixedTranslationVector(59.128290f, 3.200000f, -24.491740f),
    StandardFixedTranslationVector(62.082000f, 0.000000f, -15.550732f),
    StandardFixedTranslationVector(59.128290f, 3.200000f, -24.491740f),
    StandardFixedTranslationVector(56.442961f, 6.400000f, -30.169391f),
    StandardFixedTranslationVector(53.214055f, 3.200000f, -35.556495f),
    StandardFixedTranslationVector(57.855315f, 4.800000f, -27.363526f),
    StandardFixedTranslationVector(56.442961f, 3.200000f, -30.169391f),
    StandardFixedTranslationVector(54.894631f, 4.800000f, -32.902576f),
    StandardFixedTranslationVector(54.894631f, 0.000000f, -32.902576f),
    StandardFixedTranslationVector(49.472669f, 0.800000f, -40.601170f),
    StandardFixedTranslationVector(53.214055f, 3.200000f, -35.556495f),
    StandardFixedTranslationVector(51.405282f, 4.800000f, -38.124756f),
    StandardFixedTranslationVector(47.420872f, 3.200000f, -42.979773f),
    StandardFixedTranslationVector(49.472669f, 0.800000f, -40.601170f),
    StandardFixedTranslationVector(51.405282f, 4.800000f, -38.124756f),
    StandardFixedTranslationVector(47.420872f, 3.200000f, -42.979773f),
    StandardFixedTranslationVector(45.254834f, 3.200000f, -45.254834f),
    StandardFixedTranslationVector(45.254834f, 0.000000f, -45.254834f),
};

static constexpr uint16_t kBackground2Edges[][2] =
{
    { 0, 1 }, { 2, 3 }, { 4, 5 }, { 6, 7 }, { 7, 8 }, { 8, 9 }, { 9, 10 }, { 10, 11 }, { 11, 12 }, { 12, 13 }, { 13, 14 }, { 15, 16 }, { 16, 17 }, { 18, 19 }, { 19, 20 }, { 21, 22 }, { 22, 23 }, { 23, 24 }, { 24, 25 }, { 25, 26 }, { 26, 27 }, { 28, 29 },
};

static constexpr Intensity kBackground2Intensities[] =
{
    0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f,
};

static constexpr StandardFixedTranslationVector kBackground3Points[] =
{
    StandardFixedTranslationVector(45.254834f, 3.200000f, -45.254834f),
    StandardFixedTranslationVector(40.601170f, 0.000000f, -49.472669f),
    StandardFixedTranslationVector(45.254834f, 3.200000f, -45.254834f),
    StandardFixedTranslationVector(35.556495f, 0.000000f, -53.214055f),
    StandardFixedTranslationVector(21.560951f, 0.000000f, -60.258820f),
    StandardFixedTranslationVector(12.485781f, 3.200000f, -62.770258f),
    StandardFixedTranslationVector(9.390750f, 0.000000f, -63.307297f),
    StandardFixedTranslationVector(12.485781f, 3.200000f, -62.770258f),
    StandardFixedTranslationVector(9.390750f, 6.400000f, -63.307297f),
    StandardFixedTranslationVector(6.273097f, 0.000000f, -63.691823f),
    StandardFixedTranslationVector(3.140331f, 0.000000f, -63.922909f),
    StandardFixedTranslationVector(9.390750f, 6.400000f, -63.307297f),
    StandardFixedTranslationVector(6.273097f, 3.200000f, -63.691823f),
    StandardFixedTranslationVector(3.140331f, 6.400000f, -63.922909f),
    StandardFixedTranslationVector(-0.000000f, 3.200000f, -64.000000f),
    StandardFixedTranslationVector(-0.000000f, 0.000000f, -64.000000f),
};

static constexpr uint16_t kBackground3Edges[][2] =
{
    { 0, 1 }, { 2, 3 }, { 4, 5 }, { 5, 6 }, { 7, 8 }, { 8, 9 }, { 10, 11 }, { 12, 13 }, { 13, 14 },
};

static constexpr Intensity kBackground3Intensities[] =
{
    0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f,
};

static constexpr StandardFixedTranslationVector kBackground4Points[] =
{
    StandardFixedTranslationVector(-0.000000f, 3.200000f, -64.000000f),
    StandardFixedTranslationVector(-6.273097f, 6.400000f, -63.691823f),
    StandardFixedTranslationVector(-9.390750f, 0.000000f, -63.307297f),
    StandardFixedTranslationVector(-12.485781f, 0.000000f, -62.770258f),
    StandardFixedTranslationVector(-6.273097f, 6.400000f, -63.691823f),
    StandardFixedTranslationVector(-9.390750f, 3.200000f, -63.307297f),
    StandardFixedTranslationVector(-12.485781f, 4.800000f, -62.770258f),
    StandardFixedTranslationVector(-21.560951f, 0.000000f, -60.258820f),
    StandardFixedTranslationVector(-32.902576f, 0.000000f, -54.894631f),
    StandardFixedTranslationVector(-45.254834f, 3.200000f, -45.254834f),
    StandardFixedTranslationVector(-45.254834f, 0.000000f, -45.254834f),
};

static constexpr uint16_t kBackground4Edges[][2] =
{
    { 0, 1 }, { 1, 2 }, { 3, 4 }, { 5, 6 }, { 6, 7 }, { 8, 9 },
};

static constexpr Intensity kBackground4Intensities[] =
{
    0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f,
};

static constexpr StandardFixedTranslationVector kBackground5Points[] =
{
    StandardFixedTranslationVector(-45.254834f, 3.200000f, -45.254834f),
    StandardFixedTranslationVector(-49.472669f, 3.200000f, -40.601170f),
    StandardFixedTranslationVector(-60.258820f, 0.000000f, -21.560951f),
    StandardFixedTranslationVector(-59.128290f, 4.800000f, -24.491740f),
    StandardFixedTranslationVector(-56.442961f, 1.600000f, -30.169391f),
    StandardFixedTranslationVector(-60.258820f, 0.000000f, -21.560951f),
    StandardFixedTranslationVector(-62.770258f, 6.400000f, -12.485781f),
    StandardFixedTranslationVector(-63.691823f, 2.400000f, -6.273097f),
    StandardFixedTranslationVector(-63.518690f, 0.000000f, -7.834283f),
    StandardFixedTranslationVector(-63.980724f, 9.600000f, -1.570639f),
    StandardFixedTranslationVector(-63.987275f, 8.900000f, -1.276187f),
    StandardFixedTranslationVector(-63.995181f, 9.400000f, -0.785378f),
    StandardFixedTranslationVector(-63.998118f, 8.800000f, -0.490869f),
    StandardFixedTranslationVector(-64.000000f, 9.600000f, 0.000000f),
    StandardFixedTranslationVector(-64.000000f, 0.000000f, 0.000000f),
};

static constexpr uint16_t kBackground5Edges[][2] =
{
    { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 }, { 5, 6 }, { 6, 7 }, { 8, 9 }, { 9, 10 }, { 10, 11 }, { 11, 12 }, { 12, 13 },
};

static constexpr Intensity kBackground5Intensities[] =
{
    0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f,
};

static constexpr StandardFixedTranslationVector kBackground6Points[] =
{
    StandardFixedTranslationVector(-64.000000f, 9.600000f, 0.000000f),
    StandardFixedTranslationVector(-63.691823f, 0.000000f, 6.273097f),
    StandardFixedTranslationVector(-62.082000f, 6.400000f, 15.550732f),
    StandardFixedTranslationVector(-60.258820f, 0.000000f, 21.560951f),
    StandardFixedTranslationVector(-57.855315f, 0.000000f, 27.363526f),
    StandardFixedTranslationVector(-62.082000f, 6.400000f, 15.550732f),
    StandardFixedTranslationVector(-60.258820f, 3.200000f, 21.560951f),
    StandardFixedTranslationVector(-57.855315f, 6.400000f, 27.363526f),
    StandardFixedTranslationVector(-51.405282f, 0.000000f, 38.124756f),
    StandardFixedTranslationVector(-54.894631f, 3.200000f, 32.902576f),
    StandardFixedTranslationVector(-51.405282f, 4.800000f, 38.124756f),
    StandardFixedTranslationVector(-49.472669f, 0.000000f, 40.601170f),
    StandardFixedTranslationVector(-51.405282f, 4.800000f, 38.124756f),
    StandardFixedTranslationVector(-45.254834f, 0.000000f, 45.254834f),
};

static constexpr uint16_t kBackground6Edges[][2] =
{
    { 0, 1 }, { 1, 2 }, { 2, 3 }, { 4, 5 }, { 6, 7 }, { 7, 8 }, { 9, 10 }, { 10, 11 }, { 12, 13 },
};

static constexpr Intensity kBackground6Intensities[] =
{
    0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f, 0.428571f,
};

static constexpr StandardFixedTranslationVector kBackground7Points[] =
{
    StandardFixedTranslationVector(-30.169391f, 0.000000f, 56.442961f),
    StandardFixedTranslationVector(-9.390750f, 3.200000f, 63.307297f),
    StandardFixedTranslationVector(-3.140331f, 0.000000f, 63.922909f),
    StandardFixedTranslationVector(-6.273097f, 1.600000f, 63.691823f),
    StandardFixedTranslationVector(0.000000f, 6.400000f, 64.000000f),
    StandardFixedTranslationVector(0.000000f, 0.000000f, 64.000000f),
};

static constexpr uint16_t kBackground7Edges[][2] =
{
    { 0, 1 }, { 1, 2 }, { 3, 4 },
};

static constexpr Intensity kBackground7Intensities[] =
{
    0.428571f, 0.428571f, 0.428571f,
};

constexpr Shape3D kBackgroundShapes[] = 
{
    SHAPE_3D_2(kBackground0Points, kBackground0Edges, kBackground0Intensities),
    SHAPE_3D_2(kBackground1Points, kBackground1Edges, kBackground1Intensities),
    SHAPE_3D_2(kBackground2Points, kBackground2Edges, kBackground2Intensities),
    SHAPE_3D_2(kBackground3Points, kBackground3Edges, kBackground3Intensities),
    SHAPE_3D_2(kBackground4Points, kBackground4Edges, kBackground4Intensities),
    SHAPE_3D_2(kBackground5Points, kBackground5Edges, kBackground5Intensities),
    SHAPE_3D_2(kBackground6Points, kBackground6Edges, kBackground6Intensities),
    SHAPE_3D_2(kBackground7Points, kBackground7Edges, kBackground7Intensities),
};

static constexpr StandardFixedTranslationVector kHorizonPoints[] =
{
    StandardFixedTranslationVector(-512, 0, -512),
    StandardFixedTranslationVector(-512, 0,  512),
    StandardFixedTranslationVector( 512, 0,  512),
    StandardFixedTranslationVector( 512, 0, -512),
};

static constexpr uint16_t kHorizonEdges[][2] =
{
    { 0, 1 }, { 1, 2 }, { 2, 3 }, {3, 0},
};

constexpr Shape3D kHorizonShape = SHAPE_3D(kHorizonPoints, kHorizonEdges);

void Background::Draw(DisplayList& displayList, const Camera& camera)
{
    constexpr Intensity intensity = kIntensityAdjustment * 1.2f;
    FixedTransform3D backgroundToWorld(camera.GetPosition());
    for(uint i = 0; i < 8; ++i)
    {
        kBackgroundShapes[i].Draw(displayList, backgroundToWorld, camera, intensity);
    }
    kHorizonShape.Draw(displayList, backgroundToWorld, camera, intensity * 0.428571f);
}
