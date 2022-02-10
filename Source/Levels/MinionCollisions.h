#pragma once

#include "Minions/Minion.h"

namespace Mario::Collisions
{
void updateMinionCollisions(MinionsVector& lMinion)
{
    for (int i = 0; i < lMinion.size(); i++)
    {
        for (int j = 0; j < lMinion[i].size(); j++)
        {
            auto current = lMinion[i][j];

            if (!current->collisionOnlyWithPlayer /*&& lMinion[i][j]->minionSpawned*/
                && current->deadTime < 0)
            {
                // ----- WITH MINIONS IN SAME LIST
                for (int k = j + 1; k < lMinion[i].size(); k++)
                {
                    auto next = lMinion[i][k];

                    if (!next->collisionOnlyWithPlayer /*&& lMinion[i][k]->minionSpawned*/
                        && next->deadTime < 0)
                    {
                        if (current->getXPos() < next->getXPos())
                        {
                            if (current->getXPos() + current->iHitBoxX
                                    >= next->getXPos()
                                && current->getXPos() + current->iHitBoxX
                                       <= next->getXPos() + next->iHitBoxX
                                && ((current->getYPos()
                                         <= next->getYPos() + next->iHitBoxY
                                     && current->getYPos() + current->iHitBoxY
                                            >= next->getYPos() + next->iHitBoxY)
                                    || (next->getYPos()
                                            <= current->getYPos() + current->iHitBoxY
                                        && next->getYPos() + next->iHitBoxY
                                               >= current->getYPos()
                                                      + current->iHitBoxY)))
                            {
                                if (current->killOtherUnits && current->moveSpeed > 0
                                    && next->minionSpawned)
                                {
                                    next->setMinionState(-2);
                                    current->collisionWithAnotherUnit();
                                }

                                if (next->killOtherUnits && next->moveSpeed > 0
                                    && current->minionSpawned)
                                {
                                    current->setMinionState(-2);
                                    next->collisionWithAnotherUnit();
                                }

                                if (current->getYPos() - 4
                                        <= next->getYPos() + next->iHitBoxY
                                    && current->getYPos() + 4
                                           >= next->getYPos() + next->iHitBoxY)
                                {
                                    next->onAnotherMinion = true;
                                }
                                else if (next->getYPos() - 4
                                             <= current->getYPos()
                                                    + current->iHitBoxY
                                         && next->getYPos() + 4
                                                >= current->getYPos()
                                                       + current->iHitBoxY)
                                {
                                    current->onAnotherMinion = true;
                                }
                                else
                                {
                                    current->collisionEffect();
                                    next->collisionEffect();
                                }
                            }
                        }
                        else
                        {
                            if (next->getXPos() + next->iHitBoxX
                                    >= current->getXPos()
                                && next->getXPos() + next->iHitBoxX
                                       <= current->getXPos() + current->iHitBoxX
                                && ((current->getYPos()
                                         <= next->getYPos() + next->iHitBoxY
                                     && current->getYPos() + current->iHitBoxY
                                            >= next->getYPos() + next->iHitBoxY)
                                    || (next->getYPos()
                                            <= current->getYPos() + current->iHitBoxY
                                        && next->getYPos() + next->iHitBoxY
                                               >= current->getYPos()
                                                      + current->iHitBoxY)))
                            {
                                if (current->killOtherUnits && current->moveSpeed > 0
                                    && next->minionSpawned)
                                {
                                    next->setMinionState(-2);
                                    current->collisionWithAnotherUnit();
                                }

                                if (next->killOtherUnits && next->moveSpeed > 0
                                    && current->minionSpawned)
                                {
                                    current->setMinionState(-2);
                                    next->collisionWithAnotherUnit();
                                }

                                if (current->getYPos() - 4
                                        <= next->getYPos() + next->iHitBoxY
                                    && current->getYPos() + 4
                                           >= next->getYPos() + next->iHitBoxY)
                                {
                                    next->onAnotherMinion = true;
                                }
                                else if (next->getYPos() - 4
                                             <= current->getYPos()
                                                    + current->iHitBoxY
                                         && next->getYPos() + 4
                                                >= current->getYPos()
                                                       + current->iHitBoxY)
                                {
                                    current->onAnotherMinion = true;
                                }
                                else
                                {
                                    current->collisionEffect();
                                    next->collisionEffect();
                                }
                            }
                        }
                    }
                }

                // ----- WITH MINIONS IN OTHER LIST
                if (i + 1 < lMinion.size())
                {
                    for (auto& k: lMinion[i + 1])
                    {
                        if (!k->collisionOnlyWithPlayer /*&& lMinion[i + 1][k]->minionSpawned*/
                            && k->deadTime < 0)
                        {
                            if (current->getXPos() < k->getXPos())
                            {
                                if (current->getXPos() + current->iHitBoxX
                                        >= k->getXPos()
                                    && current->getXPos() + current->iHitBoxX
                                           <= k->getXPos() + k->iHitBoxX
                                    && ((current->getYPos()
                                             <= k->getYPos() + k->iHitBoxY
                                         && current->getYPos() + current->iHitBoxY
                                                >= k->getYPos() + k->iHitBoxY)
                                        || (k->getYPos() <= current->getYPos()
                                                                + current->iHitBoxY
                                            && k->getYPos() + k->iHitBoxY
                                                   >= current->getYPos()
                                                          + current->iHitBoxY)))
                                {
                                    if (current->killOtherUnits
                                        && current->moveSpeed > 0
                                        && k->minionSpawned)
                                    {
                                        k->setMinionState(-2);
                                        current->collisionWithAnotherUnit();
                                    }

                                    if (k->killOtherUnits && k->moveSpeed > 0
                                        && current->minionSpawned)
                                    {
                                        current->setMinionState(-2);
                                        k->collisionWithAnotherUnit();
                                    }

                                    if (current->getYPos() - 4
                                            <= k->getYPos() + k->iHitBoxY
                                        && current->getYPos() + 4
                                               >= k->getYPos() + k->iHitBoxY)
                                    {
                                        k->onAnotherMinion = true;
                                    }
                                    else if (k->getYPos() - 4
                                                 <= current->getYPos()
                                                        + current->iHitBoxY
                                             && k->getYPos() + 4
                                                    >= current->getYPos()
                                                           + current->iHitBoxY)
                                    {
                                        current->onAnotherMinion = true;
                                    }
                                    else
                                    {
                                        current->collisionEffect();
                                        k->collisionEffect();
                                    }
                                }
                            }
                            else
                            {
                                if (k->getXPos() + k->iHitBoxX >= current->getXPos()
                                    && k->getXPos() + k->iHitBoxX
                                           < current->getXPos() + current->iHitBoxX
                                    && ((current->getYPos()
                                             <= k->getYPos() + k->iHitBoxY
                                         && current->getYPos() + current->iHitBoxY
                                                >= k->getYPos() + k->iHitBoxY)
                                        || (k->getYPos() <= current->getYPos()
                                                                + current->iHitBoxY
                                            && k->getYPos() + k->iHitBoxY
                                                   >= current->getYPos()
                                                          + current->iHitBoxY)))
                                {
                                    if (current->killOtherUnits
                                        && current->moveSpeed > 0
                                        && k->minionSpawned)
                                    {
                                        k->setMinionState(-2);
                                        current->collisionWithAnotherUnit();
                                    }

                                    if (k->killOtherUnits && k->moveSpeed > 0
                                        && current->minionSpawned)
                                    {
                                        current->setMinionState(-2);
                                        k->collisionWithAnotherUnit();
                                    }
                                    /*
									if(lMinion[i][j]->getYPos() + lMinion[i][j]->iHitBoxY < lMinion[i + 1][k]->getYPos() + lMinion[i + 1][k]->iHitBoxY) {
										lMinion[i][j]->onAnotherMinion = true;
										continue;
									} else {
										lMinion[i + 1][k]->onAnotherMinion = true;
										continue;
									}*/

                                    if (current->getYPos() - 4
                                            <= k->getYPos() + k->iHitBoxY
                                        && current->getYPos() + 4
                                               >= k->getYPos() + k->iHitBoxY)
                                    {
                                        k->onAnotherMinion = true;
                                    }
                                    else if (k->getYPos() - 4
                                                 <= current->getYPos()
                                                        + current->iHitBoxY
                                             && k->getYPos() + 4
                                                    >= current->getYPos()
                                                           + current->iHitBoxY)
                                    {
                                        current->onAnotherMinion = true;
                                    }
                                    else
                                    {
                                        current->collisionEffect();
                                        k->collisionEffect();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
} // namespace Mario::Collisions