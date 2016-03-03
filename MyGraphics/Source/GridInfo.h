#pragma once

#define TileWidth 48
#define TileHeight 48

#define NumberOfTilesX 21
#define NumberOfTilesY 13

#define CellWidth NumberOfTilesX * TileWidth
#define CellHeight NumberOfTilesY * TileHeight

#define GridWidth CellWidth
#define GridHeight CellHeight

#define NumberOfPartitionsX 4
#define NumberOfPartitionsY 4

#define NumberOfPartitions NumberOfPartitionsX*NumberOfPartitionsY

#define PartitionWidth GridWidth / NumberOfPartitions
#define PartitionHeight GridHeight / NumberOfPartitions