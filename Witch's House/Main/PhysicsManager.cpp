#include "PhysicsManager.h"
#include "Camera.h"

#include "Input.h"

void PhysicsManager::Render(HDC hdc)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));

	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	if (showCollider)
	{
		for (int i = (int)g_cameraPosY; i < (int)g_cameraPosY + TILE_COUNT_Y; ++i)
		{
			for (int j = (int)g_cameraPosX; j < (int)g_cameraPosX + TILE_COUNT_X; ++j)
			{
				if (collider[i][j] != nullptr)
				{
					Rectangle(hdc,
						collider[i][j]->left - TILE_SIZE * (int)(g_cameraPosX),
						collider[i][j]->top - TILE_SIZE * (int)(g_cameraPosY),
						collider[i][j]->right - TILE_SIZE * (int)(g_cameraPosX),
						collider[i][j]->bottom - TILE_SIZE * (int)(g_cameraPosY)
					);
				}
			}
		}
	}

	if (Input::GetButtonDown(VK_SPACE))
	{
		showCollider = showCollider == true ? false : true;
	}

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);

}
