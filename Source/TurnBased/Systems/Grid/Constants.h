#pragma once

namespace Grid
{
	class FConstants
	{
	public:
		struct FDirections
		{
			const inline static FVector2D North = FVector2D(0,1);
			const inline static FVector2D East = FVector2D(1,0);
			const inline static FVector2D South = FVector2D(0,-1);
			const inline static FVector2D West = FVector2D(-1,0);
		};

		struct FGridSettings
		{
			const inline static float HorizontalGridSpace = 100;
			const inline static float HorizontalGridSize = 100;
			const inline static float VerticalGridSpace = 100;
			const inline static float VerticalGridSize = 100;
		};
	};
}

