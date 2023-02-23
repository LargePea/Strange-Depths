#include "Skeleton.h"
#include "ItemDictionary.h"

Skeleton::Skeleton() :
	Enemy(15, 5, 2, .2f, 4.5f, "Skeleton", 20, 0.4f, Image(SKELETON, 2, { 50, 12 })) {
	static ItemDictionary instance = ItemDictionary::Instance();
	static LootTable skeletonLootTable({
		{instance.GetItem("Bone"), 10},
		{instance.GetItem("Scrap Cloth"), 20},
		{instance.GetItem("Rusted Sword"), 5},
		{instance.GetPotion("Heal"), 6},
		{instance.GetPotion("Life Steal"), 3},
		{instance.GetEnchant("Skeleton"), 1}
		});

	_possibleDrops = skeletonLootTable;



	_enemyAnimator = new Animator(
		{
		AnimationClip(
			{
				{1, Image(SKELETON, 2, { 50, 11 })},
				{5, Image(SKELETON, 2, { 50, 12 })},
				{10, Image(SKELETON, 2, { 50, 13 })},
				{15, Image(SKELETON, 2, { 50, 13 })}
			})
		}, &_baseImage);
}