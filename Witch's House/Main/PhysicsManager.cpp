#include "PhysicsManager.h"
#include "Camera.h"

void PhysicsManager::Render(HDC hdc)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));

	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	if (showCollider)
	{
		for (int i = g_cameraPosY; i < g_cameraPosY + TILE_COUNT_Y; ++i)
		{
			for (int j = g_cameraPosX; j < g_cameraPosX + TILE_COUNT_X; ++j)
			{
				if (collider[i][j] != nullptr)
				{
					cout << i << " " << j << " asdasd" << endl;
					Rectangle(hdc,
						collider[i][j]->left - TILE_SIZE * (g_cameraPosX),
						collider[i][j]->top - TILE_SIZE * (g_cameraPosY),
						collider[i][j]->right - TILE_SIZE * (g_cameraPosX),
						collider[i][j]->bottom - TILE_SIZE * (g_cameraPosY)
					);
				}
			}
		}
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
		showCollider = showCollider == true ? false : true;
	}

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);

}
