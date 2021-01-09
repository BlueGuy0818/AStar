#include <stdlib.h>
#include "PathFind.h"

PathFind::PathFind()
{
}

PathFind::~PathFind()
{
}

static PathFind* pathFind = NULL;

PathFind* PathFind::getTheOnlyInstance()
{
	if (!pathFind)
	{
		pathFind = new PathFind();
	}

	return pathFind;
}

// A*初始化
Astar* PathFind::newAstar()
{
	Astar* astar = (Astar*)malloc(sizeof(Astar));
    astar->openHead = (AstartListNode*)malloc(sizeof(AstartListNode));
    astar->closedHead = (AstartListNode*)malloc(sizeof(AstartListNode));
    astar->openHead->next = NULL;
    astar->closedHead->next = NULL;
    return astar;
}

// A*释放
void PathFind::deleteAstar(Astar* astar)
{
    while (astar->openHead != NULL)
    {
        AstartListNode* t = astar->openHead;
        astar->openHead = astar->openHead->next;
        free(t);
        t = NULL;
    }

	while (astar->closedHead != NULL)
    {
        AstartListNode* t = astar->closedHead;
        astar->closedHead = astar->closedHead->next;
        free(t);
        t = NULL;
    }

	free(astar);
}

// 结点初始化
void PathFind::AstarNodeInit(AstartListNode* current, AstartListNode* father, int x, int y, int endX, int endY)
{
	current->x = x;
    current->y = y;
    current->father = father;
    current->next = NULL;

    if (father != NULL)
    {
        current->f = father->f + 1;
    }
    else
    {
        current->f = 0;
    }

    current->g = abs(endX - x) + abs(endY - y);
    current->h = current->f + current->g;
}

// 取得成本最小的结点
AstartListNode* PathFind::AstarGetMinCostList(Astar* astar)
{
	AstartListNode* min = astar->openHead->next;
    AstartListNode* current = min->next;

    while (current != NULL)
    {
        if (current->h < min->h)
        {
            min = current;
        }

        current = current->next;
    }

    return min;
}

// 添加结点到链表
void PathFind::AstarAddNode(AstartListNode* head, AstartListNode* node)
{
	while (head->next != NULL)
    {
        head = head->next;
    }

    head->next = node;
}

// 从链表中删除结点
void PathFind::AstarRemoveNode(AstartListNode* head, AstartListNode* node)
{
	AstartListNode* current = head;
    head = head->next;

    while (head != NULL)
    {
        if (head == node)
        {
            current->next = head->next;
            head->next = NULL;
            break;
        }
        else
        {
            current = head;
            head = head->next;
        }
    }
}

// 检查Tile是否在链表中
bool PathFind::AstarCheckNodeInList(int x, int y, AstartListNode* head)
{
	bool result = false;
    head = head->next;

    while (head != NULL)
    {
        if (head->x == x && head->y == y)
        {
            result = true;
            break;
        }
        else
        {
            head = head->next;
        }
    }

    return result;
}

// 检查Tile是否是地图的路障
bool PathFind::AstarIsBlock(int x, int y)
{
	if (x >= 0 && x < tiledMap->getMapSize().width && y >= 0 && y < tiledMap->getMapSize().height)
	{	
		CCTMXLayer* mapLayer = tiledMap->layerNamed("mainCityLayer");
		unsigned int gid = mapLayer->tileGIDAt(ccp(x, y));

		CCDictionary* tileProperty = tiledMap->propertiesForGID(gid);
		int v = ((CCString*)tileProperty->objectForKey("walk"))->intValue();

        if (v == 0)
        {
            return true;
        }
    }
    else
    {
        return false;
    }

    return false;
}

bool PathFind::AStarSearch(CCTMXTiledMap* tiledMap, int startX, int startY, int endX, int endY)
{
	astarPathCount = 0;
	astarPathList.clear();

	this->tiledMap = tiledMap;

	this->startX = startX;
	this->startY = startY;
	this->endX = endX;
	this->endY = endY;

	if (AstarIsBlock(endX, endY))
	{
		return false;
	}

	int offsetX[] = {0, 0, -1, 1, -1, -1, 1, 1};
    int offsetY[] = {1, -1, 0, 0, 1, -1, 1, -1};
    
	Astar* astar = newAstar();

    AstartListNode* currentNode = NULL;
    AstartListNode* startNode = (AstartListNode*)malloc(sizeof(AstartListNode));
    AstarNodeInit(startNode, NULL, startX, startY, endX, endY);
    // 把起始结点加入OpenList
    AstarAddNode(astar->openHead, startNode);

    // 如查OpenList不为空
    while (astar->openHead->next != NULL)
    {
        // 取得成本最小的结点
        currentNode = AstarGetMinCostList(astar);

        // 如果当前结点是目标结点
        if (currentNode->x == endX && currentNode->y == endY)
        {
            break;
        }
        else
        {
            // 把当前结点添加到Closed表中
            AstarAddNode(astar->closedHead, currentNode);
            // 把当前结点从Open表中删除
            AstarRemoveNode(astar->openHead, currentNode);

            for (int i = 0; i < 8; i++)
            {
                int x = currentNode->x + offsetX[i];
                int y = currentNode->y + offsetY[i];

				if (x < 0 || x >= tiledMap->getMapSize().width || y < 0 || y >= tiledMap->getMapSize().height)
                {
                    continue;
                }
                else
                {
                    if (!AstarCheckNodeInList(x, y, astar->openHead)
                        && !AstarCheckNodeInList(x, y, astar->closedHead)
                        && !AstarIsBlock(x, y)
                       )
                    {
                        AstartListNode* endNode = (AstartListNode*)malloc(sizeof(AstartListNode));
                        AstarNodeInit(endNode, currentNode, x, y, endX, endY);
                        AstarAddNode(astar->openHead, endNode);
                    }
                }
            }
        }
    }

    if (astar->openHead->next == NULL && (currentNode->x != endX || currentNode->y != endY))
    {
        astarPathCount = 0;
        return false;
    }
    else
    {
        while (currentNode != NULL)
        {
			CCPoint tilePoint;
			tilePoint.x = currentNode->x;
			tilePoint.y = currentNode->y;
            
			CCTMXLayer* mapLayer = tiledMap->layerNamed("mainCityLayer");
			CCSprite* tile = mapLayer->tileAt(ccp(tilePoint.x, tilePoint.y));
			astarPathList.push_front(tilePoint);
            currentNode = currentNode->father;
            astarPathCount++;
		}

		return true;
    }

    deleteAstar(astar);
    return false;
}