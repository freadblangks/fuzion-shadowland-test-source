/*
 * Copyright (C) 2012 - 2016 MoPCore
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Dungeon: Stormstout Brewery.
 * Description: Mob scripts.
 */

#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuras.h"
#include "SpellAuraEffects.h"
#include "Player.h"
#include "Vehicle.h"
#include "Group.h"

#include "stormstout_brewery.h"

/* Yells and events

First Alemental after Hoptallus:

Ancient Brewmaster says: Whatzit... are they... what are they doin' to our alementals?
Ancient Brewmaster yells: Hey... hey YOU! Those are OUR, flying... beer monsters?

Ancestral Brewmaster:
Ancestral Brewmaster says(1): Are these guys Alliance or Horde?
Ancestral Brewmaster says(3): Why does it matter?
Ancestral Brewmaster says(1): I need to know which side to stop rooting for!

Ancestral Brewmaster says(1): Do you think all of this fighting is educational for this group?
Ancestral Brewmaster says(2): Yes, it will drive them to read books!

Ancestral Brewmaster says(1): Do you think that undead party made it through in one piece?
Ancestral Brewmaster says(2): No, I don't think they had the guts!

Ancestral Brewmaster says(1): Do you think that we can return to life after death?
Ancestral Brewmaster says(2): Sure! That last group did about thirty times!

Ancestral Brewmaster says(1): Finally, we've seen a good group!
Ancestral Brewmaster says(3): Does that mean we can stop coming here now?

Ancestral Brewmaster says(1): How many of these outlanders does it take to paint a wall?
Ancestral Brewmaster says(3): I don't know, how many?
Ancestral Brewmaster says(1): It depends on how hard you throw them!

Ancestral Brewmaster says(1): I liked that last group!
Ancestral Brewmaster says(2): What did you like about it?
Ancestral Brewmaster says(1): I thought it was the last group!

Ancestral Brewmaster says(1): I think that druid had the hots for me!

Ancestral Brewmaster says(1): I wonder if there's anything this healer isn't good at!
Ancestral Brewmaster says(3): Sure! Choosing which group to be in!

Ancestral Brewmaster says(1): I've got a great joke for you!
Ancestral Brewmaster says(x): What's that?
Ancestral Brewmaster says(1): These guys' weapons!

Ancestral Brewmaster says(1): Just when I think a group is the worst, something wonderful happends!
Ancestral Brewmaster says(3): What's that?
Ancestral Brewmaster says(1): They leave!

Ancestral Brewmaster says(1): That last priest had me smitten!

Ancestral Brewmaster says(1): That last shaman really knew his place!
Ancestral Brewmaster says(2): And where is that?
Ancestral Brewmaster says(1): Outland!

Ancestral Brewmaster says(1): The last paladin offered me eternal salvation!
Ancestral Brewmaster says(2): What'd you say?
Ancestral Brewmaster says(1): Kings, please.

Ancestral Brewmaster says(1): This group is awful!
Ancestral Brewmaster says(3): Terrible!
Ancestral Brewmaster says(1): Disgusting!
Ancestral Brewmaster says(3): See you here tomorrow?
Ancestral Brewmaster says(1): Absolutely!

Ancestral Brewmaster says(1): This view is terrible!
Ancestral Brewmaster says(2): What, are you having trouble seeing the fight?
Ancestral Brewmaster says(1): No, I can see it perfectly!

Ancestral Brewmaster says(1): Why didn't that mage put intellect on his weapon?
Ancestral Brewmaster says(2): Because he didn't want it to be smarter than he was!

Ancestral Brewmaster says(1): You fool, you're sleeping through the fight!
Ancestral Brewmaster says(2): Who's the fool? You're watching it!

Ancestral Brewmaster says(1): You know what's the best thing about this group?
Ancestral Brewmaster says(2): What?
Ancestral Brewmaster says(1): They opened the doors so we can escape!

Ancestral Brewmaster says(1): You know, I really envy these guys!
Ancestral Brewmaster says(3): Why's that?
Ancestral Brewmaster says(1): Becose they get to spend so much time with that foxy spirit healer!

Ancestral Brewmaster says(1): You know, getting items must be hard for these guys!
Ancestral Brewmaster says(3): Why's that?
Ancestral Brewmaster says(1): Because pants never drop when they're around!

Ancestral Brewmaster says(1): I think this group will really improve with age!
Ancestral Brewmaster says(2): You think they'll get better?
Ancestral Brewmaster says(1): No, my eyesight will get worse!

Ancestral Brewmaster says(1): I think I'm going to need another drink!
Ancestral Brewmaster says(2): Why do you say that?
Ancestral Brewmaster says(1): I'm beginning to like these guys!

Ancestral Brewmaster says(1): Pay up, they made it through those alementals!
Ancestral Brewmaster says(3): Double or nothing on the next group?
*/

// Chen Stormstout / Auntie Stormstout intro yells.
enum IntroYells
{
    AUNTIE_ENTRANCE_SAY_1   = 0, // Auntie Stormstout says: Oh, hello Zan, it is good of you to visit ol' Auntie Stormstout.
    CHEN_ENTRANCE_SAY_1     = 0, // Chen Stormstout   says: I am not Zan - I am Chen Stormstout!
    AUNTIE_ENTRANCE_SAY_2   = 1, // Auntie Stormstout says: Oh, Zan! You remind me so much of your father.
    CHEN_ENTRANCE_SAY_2     = 1, // Chen Stormstout   says: Tell me, what has happened here?
    AUNTIE_ENTRANCE_SAY_3   = 2, // Auntie Stormstout says: It is certainly a nice day outside!
    CHEN_ENTRANCE_SAY_3     = 2, // Chen Stormstout   says: Where are the other Stormstouts? Why are hozen all over the brewery?
    AUNTIE_ENTRANCE_SAY_4   = 3, // Auntie Stormstout says: Have you seen the size of Esme's turnips?
    CHEN_ENTRANCE_SAY_4     = 3, // Chen Stormstout   says: Auntie Stormstout... why is the brewery abandoned?
    AUNTIE_ENTRANCE_SAY_5   = 4, // Auntie Stormstout says: Abandoned? Oh heavens no! Uncle Gao is in charge while the others are beyond the wall. Isn't that exciting?
    CHEN_ENTRANCE_SAY_5     = 4, // Chen Stormstout   says: I see - and where is Uncle Gao?
    AUNTIE_ENTRANCE_SAY_6   = 5, // Auntie Stormstout says: I have some cookies for you!
    CHEN_ENTRANCE_SAY_6     = 5, // Chen Stormstout   says: There is no time for cookies! Well, one cookie. Just one.
    CHEN_ENTRANCE_SAY_7     = 6  // Chen Stormstout   says: Wait - these are ghost cookies. These aren't filling at all!
};

// Hozen Bouncer yells.
enum BouncerYells
{
    SAY_OOK_KILLED          = 0, // You take down Ook-Ook...
    SAY_MEANS               = 1, // You know what dat mean...
    SAY_NEW_OOK             = 2, // You da new Ook!
    SAY_PARTY               = 3  // Get da party started for da new Ook!
};

// Ancestral Brewmaster yells.
enum AncestralBrewmasterYells
{
    SAY_ABM_HOPTALLUS_1     = 0, // Whatzit... are they... what are they doin' to our alementals?
    SAY_ABM_HOPTALLUS_2     = 0, // Hey... hey YOU! Those are OUR flying... beer monsters?
};

#define ANN_ILLUSION "Removing the spirit's illusion damages the hozen's fragile mind!"

enum Spells
{
    // FRIENDLY
    SPELL_AUNTIE_VISUAL     = 115618, // Auntie Stormstout visual.
    SPELL_GUSHING_BREW_BVIS = 114379, // Gushing Brew beam visual (The Great Wheel).
    SPELL_GUSHING_BREW_A    = 114380, // Gushing Brew aura (NPC that has beam cast on).
    SPELL_LEAKING_BEER_B_A  = 146604, // Dummy for NPC on Keg.
    SPELL_BEER_PUDDLE_VIS   = 112960, // Beer on ground visual.

    // HOSTILE

    // Aqua Dancer - Once killed, their deaths will damage the Sodden Hozen Brawlers for half their health.
    SPELL_AQUATIC_ILLUSION  = 107044, // Gives Sodden Hozen Brawler SPELL_WATER_STRIKE.
    SPELL_AQUAT_ILLUSION_R  = 114655, // Removal damage.

    // Fiery Trickster - Once killed, their deaths will damage the Inflamed Hozen Brawlers for half their health.
    SPELL_FIERY_ILLUSION    = 107175, // Gives Inflamed Hozen Brawler SPELL_FIRE_STRIKE.
    SPELL_FIERY_ILLUSION_R  = 114656, // Removal damage.

    // Sodded Hozen Brawler
    SPELL_WATER_STRIKE      = 107046,

    // Inflamed Hozen Brawler
    SPELL_FIRE_STRIKE       = 107176,

    // Hozen Bouncer - 2 bouncers only, after Ook-Ook. After yells they run, crash into each other, die.
    SPELL_HOZEN_DOORGUARD   = 107019,

    // Sleepy Hozen Brawler, Drunken Hozen Brawler.
    SPELL_COSMETIC_SLEEP    = 124557, // Used by Sleepy.
    SPELL_UPPERCUT          = 80182,

    // Habanero Brew
    SPELL_PROC_EXPLOSION    = 106787,
    SPELL_SPICY_EXPLOSION   = 107205,

    SPELL_BREW_BARREL_EXPL  = 107351, // Barrel monkey explosion.

    // Stout Brew Alemental
    SPELL_BREW_BOLT         = 115652,
    SPELL_BLACKOUT_BREW     = 106851,
    SPELL_BLACKOUT_DRUNK    = 106857, // At 10 stacks of SPELL_BLACKOUT_BREW.

    // Sudsy Brew Alemental
    SPELL_BREW_BOLT2        = 115650,
    SPELL_SUDS              = 116178, // Creates NPC_POOL_OF_SUDS at target location.
    AURA_SUDS               = 116179, // Periodic dmg trigger aura.
    SPELL_SUDS_DUMMY_VIS    = 119418, // Tooltip: "Can summon puddles of suds."

    // Unruly Alemental
    SPELL_BREW_BOLT3        = 118104,
    SPELL_BREWHAHA          = 118099,

    // Bubbling Brew Alemental
    SPELL_BREW_BOLT4        = 116155,
    SPELL_BUBBLE_SHIELD     = 128708,

    // Fizzy Brew Alemental
    // Uses SPELL_BREW_BOLT2.
    SPELL_CARBONATION_M     = 116162, // Missile.
    SPELL_CARBONATION_S     = 116164, // Creates NPC_CARBONATION_POOL at target location.
    AURA_CARBONATION        = 116168, // Periodic dmg trigger aura.

    // Bloated Brew Alemental
    // Uses SPELL_BREW_BOLT.
    SPELL_BLOAT             = 106546,

    // Yeasty Brew Alemental
    // Uses SPELL_BREW_BOLT4.
    // Uses Ferment in boss script.
};

enum Events
{
    // Trash

    EVENT_UPPERCUT          = 1,
    EVENT_WATER_STRIKE,
    EVENT_FIRE_STRIKE,

    EVENT_BREW_BOLT,
    EVENT_BLACKOUT_BREW,
    EVENT_BREW_BOLT2,
    EVENT_SUDS,
    EVENT_BREW_BOLT3,
    EVENT_CARBONATION,
    EVENT_BLOAT,
    EVENT_BUBBLE_SHIELD,
    EVENT_BREW_BOLT4,

    // Hozen Bouncer
    EVENT_CHECK_OOK,
    EVENT_SAY_OOK_KILLED,
    EVENT_SAY_MEANS,
    EVENT_SAY_NEW_OOK,
    EVENT_SAY_PARTY,
    EVENT_RUN_AND_CRASH,
    EVENT_BOUNCER_DIE,

    // Chen Stormstout / Auntie Stormstout intro event
    EVENT_AUNTIE_ENTRANCE_SAY_1,
    EVENT_CHEN_ENTRANCE_SAY_1,
    EVENT_AUNTIE_ENTRANCE_SAY_2,
    EVENT_CHEN_ENTRANCE_SAY_2,
    EVENT_AUNTIE_ENTRANCE_SAY_3,
    EVENT_CHEN_ENTRANCE_SAY_3,
    EVENT_AUNTIE_ENTRANCE_SAY_4,
    EVENT_CHEN_ENTRANCE_SAY_4,
    EVENT_AUNTIE_ENTRANCE_SAY_5,
    EVENT_CHEN_ENTRANCE_SAY_5,
    EVENT_AUNTIE_ENTRANCE_SAY_6,
    EVENT_CHEN_ENTRANCE_SAY_6,
    EVENT_CHEN_ENTRANCE_SAY_7,

    // Ancestral Brewmaster
    EVENT_SPEAK_HOPTALLUS_1,
    EVENT_SPEAK_HOPTALLUS_2,
    EVENT_SPEAK_RANDOM
};

enum Actions
{
    ACTION_START_INTRO      = 0, // Chen Stormstout intro start.
};

// Instance Scripted events and dialogues.

class at_stormstout_brewery_entrance : public AreaTriggerScript
{
    public:
        at_stormstout_brewery_entrance() : AreaTriggerScript("at_stormstout_brewery_entrance") { }

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
        {
            if (!player)
                return true;

            InstanceScript* instance = player->GetInstanceScript();
            if (!instance)
                return true;

            if (instance->GetData(DATA_HOZEN_KILLED) < HOZEN_KILLS_NEEDED && instance->GetData(DATA_OOK_SUMMONED) == false && instance->GetData(DATA_OOKOOK_EVENT) != DONE)
            {
                // Add the Hozen Counter aura.
                if (player->GetGroup())
                {
                    for (GroupReference* itr = player->GetGroup()->GetFirstMember(); itr != NULL; itr = itr->next())
                    {
                        if (Player* member = itr->getSource())
                        {
                            if (!member->HasAura(SPELL_BANANA_BAR))
                            {
                                member->AddAura(SPELL_BANANA_BAR, member);
                                member->SetPower(POWER_ALTERNATE_POWER, instance->GetData(DATA_HOZEN_KILLED));
                            }
                        }
                    }
                }
                else
                {
                    player->AddAura(SPELL_BANANA_BAR, player);
                    player->SetPower(POWER_ALTERNATE_POWER, instance->GetData(DATA_HOZEN_KILLED));
                }

                // Make the intro event start, once.
                if (Creature* auntieStormstout = player->FindNearestCreature(NPC_AUNTIE_STORMSTOUT, 100.0f, true))
                {
                    if (!auntieStormstout->HasAura(SPELL_AUNTIE_VISUAL))
                    {
                        auntieStormstout->AddAura(SPELL_AUNTIE_VISUAL, auntieStormstout);
                        if (Creature* chenStormstout = player->FindNearestCreature(NPC_CHEN_STORMSTOUT_ENTRANCE, 100.0f, true))
                            chenStormstout->AI()->DoAction(ACTION_START_INTRO);
                    }
                }
            }

            return true;
        }
};

// Chen Stormstout entrance 59704.
class npc_chen_stormstout_entrance : public CreatureScript
{
    public :
        npc_chen_stormstout_entrance() : CreatureScript("npc_chen_stormstout_entrance") { }

        struct npc_chen_stormstout_entrance_AI : public ScriptedAI
        {
            npc_chen_stormstout_entrance_AI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;
            Creature* auntieStormstout;
            bool introStarted;

            void InitializeAI()
            {
                if (!me->IsDead())
                    Reset();
            }

            void Reset()
            {
                events.Reset();
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                auntieStormstout = NULL;
                introStarted = false;
            }

            void DoAction(int32 const action)
            {
                if (action == ACTION_START_INTRO && introStarted)
                    return;

                switch (action)
                {
                    case ACTION_START_INTRO:
                        if (Creature* auntie = me->FindNearestCreature(NPC_AUNTIE_STORMSTOUT, 100.0f, true))
                            auntieStormstout = auntie;
                        introStarted = true;
                        events.ScheduleEvent(EVENT_AUNTIE_ENTRANCE_SAY_1, 1000);
                        break;

                    default: break;
                }
            };

            void UpdateAI(const uint32 diff)
            {
                events.Update(diff);

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_AUNTIE_ENTRANCE_SAY_1:
                            auntieStormstout->AI()->Talk(AUNTIE_ENTRANCE_SAY_1);
                            auntieStormstout->HandleEmote(EMOTE_ONESHOT_TALK);
                            events.ScheduleEvent(EVENT_CHEN_ENTRANCE_SAY_1, 8000);
                            break;

                        case EVENT_CHEN_ENTRANCE_SAY_1:
                            Talk(CHEN_ENTRANCE_SAY_1);
                            me->HandleEmote(EMOTE_ONESHOT_EXCLAMATION);
                            events.ScheduleEvent(EVENT_AUNTIE_ENTRANCE_SAY_2, 5000);
                            break;

                        case EVENT_AUNTIE_ENTRANCE_SAY_2:
                            auntieStormstout->AI()->Talk(AUNTIE_ENTRANCE_SAY_2);
                            auntieStormstout->HandleEmote(EMOTE_ONESHOT_TALK);
                            events.ScheduleEvent(EVENT_CHEN_ENTRANCE_SAY_2, 6000);
                            break;

                        case EVENT_CHEN_ENTRANCE_SAY_2:
                            Talk(CHEN_ENTRANCE_SAY_2);
                            me->HandleEmote(EMOTE_ONESHOT_QUESTION);
                            events.ScheduleEvent(EVENT_AUNTIE_ENTRANCE_SAY_3, 5000);
                            break;

                        case EVENT_AUNTIE_ENTRANCE_SAY_3:
                            auntieStormstout->AI()->Talk(AUNTIE_ENTRANCE_SAY_3);
                            auntieStormstout->HandleEmote(EMOTE_ONESHOT_EXCLAMATION);
                            events.ScheduleEvent(EVENT_CHEN_ENTRANCE_SAY_3, 5000);
                            break;

                        case EVENT_CHEN_ENTRANCE_SAY_3:
                            Talk(CHEN_ENTRANCE_SAY_3);
                            me->HandleEmote(EMOTE_ONESHOT_QUESTION);
                            events.ScheduleEvent(EVENT_AUNTIE_ENTRANCE_SAY_4, 9000);
                            break;

                        case EVENT_AUNTIE_ENTRANCE_SAY_4:
                            auntieStormstout->AI()->Talk(AUNTIE_ENTRANCE_SAY_4);
                            auntieStormstout->HandleEmote(EMOTE_ONESHOT_QUESTION);
                            events.ScheduleEvent(EVENT_CHEN_ENTRANCE_SAY_4, 5500);
                            break;

                        case EVENT_CHEN_ENTRANCE_SAY_4:
                            Talk(CHEN_ENTRANCE_SAY_4);
                            me->HandleEmote(EMOTE_ONESHOT_TALK);
                            events.ScheduleEvent(EVENT_AUNTIE_ENTRANCE_SAY_5, 6500);
                            break;

                        case EVENT_AUNTIE_ENTRANCE_SAY_5:
                            auntieStormstout->AI()->Talk(AUNTIE_ENTRANCE_SAY_5);
                            auntieStormstout->HandleEmote(EMOTE_ONESHOT_TALK);
                            events.ScheduleEvent(EVENT_CHEN_ENTRANCE_SAY_5, 11000);
                            break;

                        case EVENT_CHEN_ENTRANCE_SAY_5:
                            Talk(CHEN_ENTRANCE_SAY_5);
                            me->HandleEmote(EMOTE_ONESHOT_TALK);
                            events.ScheduleEvent(EVENT_AUNTIE_ENTRANCE_SAY_6, 4500);
                            break;

                        case EVENT_AUNTIE_ENTRANCE_SAY_6:
                            auntieStormstout->AI()->Talk(AUNTIE_ENTRANCE_SAY_6);
                            auntieStormstout->HandleEmote(EMOTE_ONESHOT_POINT);
                            events.ScheduleEvent(EVENT_CHEN_ENTRANCE_SAY_6, 4500);
                            break;

                        case EVENT_CHEN_ENTRANCE_SAY_6:
                            Talk(CHEN_ENTRANCE_SAY_6);
                            me->HandleEmote(EMOTE_ONESHOT_NO);
                            events.ScheduleEvent(EVENT_CHEN_ENTRANCE_SAY_7, 15000);
                            break;

                        case EVENT_CHEN_ENTRANCE_SAY_7:
                            Talk(CHEN_ENTRANCE_SAY_7);
                            me->HandleEmote(EMOTE_ONESHOT_EAT);
                            break;

                        default: break;
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_chen_stormstout_entrance_AI(creature);
        }
};

// Ancestral Brewmaster 59075.
class npc_ancestral_brewmaster : public CreatureScript
{
    public :
        npc_ancestral_brewmaster() : CreatureScript("npc_ancestral_brewmaster") { }

        struct npc_ancestral_brewmaster_AI : public ScriptedAI
        {
            npc_ancestral_brewmaster_AI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;
            bool said, alone, hasTwo, hasThree;

            void InitializeAI()
            {
                if (!me->IsDead())
                    Reset();
            }

            void Reset()
            {
                events.Reset();
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                said = false;
                hasTwo = me->FindNearestCreature(NPC_ANCESTRAL_BREWMASTER_2, 4.0f, true) ? true : false;
                hasThree = (hasTwo && me->FindNearestCreature(NPC_ANCESTRAL_BREWMASTER_3, 4.0f, true)) ? true : false;
                alone = (!hasTwo && !hasThree) ? true : false;
            }

            void UpdateAI(const uint32 diff)
            {
                // Check stuff for the Brewmasters after Hoptallus.
                if (!said && hasTwo && instance->GetData(DATA_HOPTALLUS_EVENT) == DONE)
                {
                    if (me->FindNearestPlayer(20.0f, true))
                    {
                        if (Creature* Alemental = me->FindNearestCreature(NPC_BLOATED_BREW_ALEMENTAL, 20.0f, true))
                        {
                            if (Alemental->isInCombat())
                            {
                                events.ScheduleEvent(EVENT_SPEAK_HOPTALLUS_1, 2000);
                                said = true;
                            }
                        }
                    }
                }

                events.Update(diff);

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_SPEAK_HOPTALLUS_1:
                            Talk(SAY_ABM_HOPTALLUS_1);
                            me->HandleEmote(EMOTE_ONESHOT_QUESTION);
                            events.ScheduleEvent(EVENT_SPEAK_HOPTALLUS_2, 8000);
                            break;

                        case EVENT_SPEAK_HOPTALLUS_2:
                            if (Creature* brewMaster2 = me->FindNearestCreature(NPC_ANCESTRAL_BREWMASTER_2, 5.0f, true))
                            {
                                brewMaster2->AI()->Talk(SAY_ABM_HOPTALLUS_2);
                                brewMaster2->HandleEmote(EMOTE_ONESHOT_EXCLAMATION);
					        }
                            break;

                        case EVENT_SPEAK_RANDOM:
                            break;

                        default: break;
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_ancestral_brewmaster_AI(creature);
        }
};

// Instance trash scripts.

// Sodden Hozen Brawler 59605.
class npc_sodden_hozen_brawler : public CreatureScript
{
    public :
        npc_sodden_hozen_brawler() : CreatureScript("npc_sodden_hozen_brawler") { }

        struct npc_sodden_hozen_brawler_AI : public ScriptedAI
        {
            npc_sodden_hozen_brawler_AI(Creature* creature) : ScriptedAI(creature), summons(me)
            {
                instance = creature->GetInstanceScript();
                summonedFirstHelper = false;
            }

            InstanceScript* instance;
            EventMap events;
            SummonList summons;
            bool summonedFirstHelper, helperDead;

            void InitializeAI()
            {
                if (!me->IsDead())
                    Reset();
            }

            void Reset()
            {
                events.Reset();
                summons.DespawnAll();
                helperDead = false;
                me->SetReactState(REACT_DEFENSIVE);

                // Summon the "helper".
                if (!summonedFirstHelper)
                {
                    me->SummonCreature(NPC_AQUA_DANCER, me->GetPositionX(), me->GetPositionY() + 4.0f, me->GetPositionZ() + 8.0f, me->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN);
                    summonedFirstHelper = true;
                }
            }

            void EnterCombat(Unit* /*who*/) { }

            void EnterEvadeMode()
            {
                Reset();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->GetMotionMaster()->MoveTargetedHome();
            }

            void JustReachedHome()
            {
                if (helperDead)
                    me->SummonCreature(NPC_AQUA_DANCER, me->GetPositionX(), me->GetPositionY() + 4.0f, me->GetPositionZ() + 8.0f, me->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN);
            }

            void JustDied(Unit* /*killer*/)
            {
                summons.DespawnAll();
            }

            void JustSummoned(Creature* summon)
            {
                summons.Summon(summon);
                summon->setActive(true);

		        if (me->isInCombat())
                    summon->SetInCombatWithZone();

                if (summon->GetEntry() == NPC_AQUA_DANCER)
                {
                    summon->SetCanFly(true);
                    summon->SetDisableGravity(true);
                    summon->SetReactState(REACT_PASSIVE);
                    summon->CastSpell(me, SPELL_AQUATIC_ILLUSION, false);
                }
            }

            void SummonedCreatureDies(Creature* summon, Unit* /*killer*/)
            {
                summons.Despawn(summon);
                me->RemoveAurasDueToSpell(SPELL_AQUATIC_ILLUSION);
                DoCast(me, SPELL_AQUAT_ILLUSION_R);
                me->MonsterTextEmote(ANN_ILLUSION, NULL, true);
                helperDead = true;
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_sodden_hozen_brawler_AI(creature);
        }
};

// Inflamed Hozen Brawler 56924.
class npc_inflamed_hozen_brawler : public CreatureScript
{
    public :
        npc_inflamed_hozen_brawler() : CreatureScript("npc_inflamed_hozen_brawler") { }

        struct npc_inflamed_hozen_brawler_AI : public ScriptedAI
        {
            npc_inflamed_hozen_brawler_AI(Creature* creature) : ScriptedAI(creature), summons(me)
            {
                instance = creature->GetInstanceScript();
                summonedFirstHelper = false;
            }

            InstanceScript* instance;
            EventMap events;
            SummonList summons;
            bool summonedFirstHelper, helperDead;

            void InitializeAI()
            {
                if (!me->IsDead())
                    Reset();
            }

            void Reset()
            {
                events.Reset();
                summons.DespawnAll();
                helperDead = false;

                // Summon the "helper".
                if (!summonedFirstHelper)
                {
                    me->SummonCreature(NPC_FIERY_TRICKSTER, me->GetPositionX(), me->GetPositionY() + 4.0f, me->GetPositionZ() + 8.0f, me->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN);
                    summonedFirstHelper = true;
                }
            }

            void EnterCombat(Unit* /*who*/) { }

            void EnterEvadeMode()
            {
                Reset();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->GetMotionMaster()->MoveTargetedHome();
            }

            void JustReachedHome()
            {
                if (helperDead)
                    me->SummonCreature(NPC_FIERY_TRICKSTER, me->GetPositionX(), me->GetPositionY() + 4.0f, me->GetPositionZ() + 8.0f, me->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN);
            }

            void JustDied(Unit* /*killer*/)
            {
                summons.DespawnAll();
            }

            void JustSummoned(Creature* summon)
            {
                summons.Summon(summon);
                summon->setActive(true);

		        if (me->isInCombat())
                    summon->SetInCombatWithZone();

                if (summon->GetEntry() == NPC_FIERY_TRICKSTER)
                {
                    summon->SetCanFly(true);
                    summon->SetDisableGravity(true);
                    summon->SetReactState(REACT_PASSIVE);
                    summon->CastSpell(me, SPELL_FIERY_ILLUSION, false);
                }
            }

            void SummonedCreatureDies(Creature* summon, Unit* /*killer*/)
            {
                summons.Despawn(summon);
                me->RemoveAurasDueToSpell(SPELL_FIERY_ILLUSION);
                DoCast(me, SPELL_FIERY_ILLUSION_R);
                me->MonsterTextEmote(ANN_ILLUSION, NULL, true);
                helperDead = true;
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_inflamed_hozen_brawler_AI(creature);
        }
};

// Hozen Bouncer 56849.
class npc_hozen_bouncer : public CreatureScript
{
    public :
        npc_hozen_bouncer() : CreatureScript("npc_hozen_bouncer") { }

        struct npc_hozen_bouncer_AI : public ScriptedAI
        {
            npc_hozen_bouncer_AI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;
            bool IsInCombat;

            void InitializeAI()
            {
                if (!me->IsDead())
                    Reset();
            }

            void Reset()
            {
                events.Reset();
                IsInCombat = false;
                me->SetReactState(REACT_DEFENSIVE);
                me->AddAura(SPELL_HOZEN_DOORGUARD, me);

                events.ScheduleEvent(EVENT_CHECK_OOK, 10000);
            }

            void EnterCombat(Unit* who)
            {
                IsInCombat = true;
                me->SetReactState(REACT_AGGRESSIVE);
                me->RemoveAurasDueToSpell(SPELL_HOZEN_DOORGUARD);
                if (Creature* doorGuard = me->FindNearestCreature(NPC_HOZEN_BOUNCER, 100.0f, true))
                    if (!doorGuard->isInCombat())
                        doorGuard->AI()->AttackStart(who);
                events.CancelEvent(EVENT_CHECK_OOK);
            }

            void EnterEvadeMode()
            {
                Reset();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->GetMotionMaster()->MoveTargetedHome();
            }

            void MovementInform(uint32 type, uint32 id)
            {
                if (!me->IsAlive() || type != POINT_MOTION_TYPE || id != 1)
                    return;

                events.ScheduleEvent(EVENT_BOUNCER_DIE, 200);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim() && IsInCombat)
                    return;

                events.Update(diff);

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_CHECK_OOK:
                            // Check for Ook-ook killed.
                            if (instance->GetBossState(DATA_OOKOOK_EVENT) == DONE)
                            {
                                // Check on Y position (only one does the talking).
                                if (me->GetPositionY() > 1303.0f)
                                    events.ScheduleEvent(EVENT_SAY_OOK_KILLED, 2000);
                                events.ScheduleEvent(EVENT_RUN_AND_CRASH, 18000);
                            }
                            else
                                events.ScheduleEvent(EVENT_CHECK_OOK, 10000);
                            break;

                        case EVENT_SAY_OOK_KILLED:
                            Talk(SAY_OOK_KILLED);
                            events.ScheduleEvent(EVENT_SAY_MEANS, 4000);
                            break;

                        case EVENT_SAY_MEANS:
                            Talk(SAY_MEANS);
                            events.ScheduleEvent(EVENT_SAY_NEW_OOK, 4000);
                            break;

                        case EVENT_SAY_NEW_OOK:
                            Talk(SAY_NEW_OOK);
                            events.ScheduleEvent(EVENT_SAY_PARTY, 3000);
                            break;

                        case EVENT_SAY_PARTY:
                            Talk(SAY_PARTY);
                            break;

                        case EVENT_RUN_AND_CRASH:
                            me->GetMotionMaster()->MovePoint(1, -747.929f, 1323.334f, 146.715f);
                            break;

                        case EVENT_BOUNCER_DIE:
                            me->Kill(me); // Die.
                            break;

                        default: break;
                    }
                }

                if (IsInCombat)
                    DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_hozen_bouncer_AI(creature);
        }
};

// Sleepy Hozen Brawler 56863, Drunken Hozen Brawler 56862.
class npc_drunken_sleepy_hozen_brawler : public CreatureScript
{
    public :
        npc_drunken_sleepy_hozen_brawler() : CreatureScript("npc_drunken_sleepy_hozen_brawler") { }

        struct npc_drunken_sleepy_hozen_brawler_AI : public ScriptedAI
        {
            npc_drunken_sleepy_hozen_brawler_AI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;

            void InitializeAI()
            {
                if (!me->IsDead())
                    Reset();
            }

            void Reset()
            {
                events.Reset();
                me->SetReactState(REACT_DEFENSIVE);

                // Add Sleep cosmetic to the Sleepy Hozen Brawlers.
                if (me->GetEntry() == NPC_SLEEPY_HOZEN_BRAWLER && !me->HasAura(SPELL_COSMETIC_SLEEP))
                    me->AddAura(SPELL_COSMETIC_SLEEP, me);
            }

            void EnterCombat(Unit* /*who*/)
            {
                if (me->GetEntry() == NPC_SLEEPY_HOZEN_BRAWLER)
                {
                    // Remove Sleep cosmetic from the Sleepy Hozen Brawlers.
                    me->RemoveAurasDueToSpell(SPELL_COSMETIC_SLEEP);

                    // Check the Habanero Brew barrels.
                    if (Creature* habanero = me->FindNearestCreature(NPC_HABANERO_BREW, 10.0f))
                        habanero->CastSpell(habanero, SPELL_SPICY_EXPLOSION, false);
                }

                events.ScheduleEvent(EVENT_UPPERCUT, urand(4000, 8000));
            }

            void EnterEvadeMode()
            {
                Reset();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->GetMotionMaster()->MoveTargetedHome();
            }

            void JustReachedHome()
            {
                // Add Sleep cosmetic to the Sleepy Hozen Brawlers.
                if (me->GetEntry() == NPC_SLEEPY_HOZEN_BRAWLER && !me->HasAura(SPELL_COSMETIC_SLEEP))
                    me->AddAura(SPELL_COSMETIC_SLEEP, me);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_UPPERCUT:
                            DoCastVictim(SPELL_UPPERCUT);
                            events.ScheduleEvent(EVENT_UPPERCUT, urand(6000, 11000));
                            break;

                        default: break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_drunken_sleepy_hozen_brawler_AI(creature);
        }
};

// Stout Brew Alemental 59519.
class npc_stout_brew_alemental : public CreatureScript
{
    public :
        npc_stout_brew_alemental() : CreatureScript("npc_stout_brew_alemental") { }

        struct npc_stout_brew_alemental_AI : public ScriptedAI
        {
            npc_stout_brew_alemental_AI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;

            void InitializeAI()
            {
                if (!me->IsDead())
                    Reset();
            }

            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit* /*who*/)
            {
                events.ScheduleEvent(EVENT_BREW_BOLT, urand(2000, 6000));
                events.ScheduleEvent(EVENT_BLACKOUT_BREW, urand(12000, 17000));
            }

            void EnterEvadeMode()
            {
                Reset();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->GetMotionMaster()->MoveTargetedHome();
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_BREW_BOLT:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                DoCast(target, SPELL_BREW_BOLT);
                            events.ScheduleEvent(EVENT_BREW_BOLT, urand(7000, 11000));
                            break;

                        case EVENT_BLACKOUT_BREW:
                            DoCast(me, SPELL_BLACKOUT_BREW);
                            events.ScheduleEvent(EVENT_BLACKOUT_BREW, urand(18000, 23000));
                            break;

                        default: break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_stout_brew_alemental_AI(creature);
        }
};

// Sudsy Brew Alemental 59522.
class npc_sudsy_brew_alemental : public CreatureScript
{
    public :
        npc_sudsy_brew_alemental() : CreatureScript("npc_sudsy_brew_alemental") { }

        struct npc_sudsy_brew_alemental_AI : public ScriptedAI
        {
            npc_sudsy_brew_alemental_AI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;

            void InitializeAI()
            {
                if (!me->IsDead())
                    Reset();
            }

            void Reset()
            {
                events.Reset();
                me->AddAura(SPELL_SUDS_DUMMY_VIS, me);
            }

            void EnterCombat(Unit* /*who*/)
            {
                events.ScheduleEvent(EVENT_BREW_BOLT2, urand(2000, 6000));
                events.ScheduleEvent(EVENT_SUDS, urand(9000, 12000));
            }

            void EnterEvadeMode()
            {
                Reset();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->GetMotionMaster()->MoveTargetedHome();
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_BREW_BOLT2:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                DoCast(target, SPELL_BREW_BOLT2);
                            events.ScheduleEvent(EVENT_BREW_BOLT2, urand(7000, 11000));
                            break;

                        case EVENT_SUDS:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                DoCast(target, SPELL_SUDS);
                            events.ScheduleEvent(EVENT_SUDS, urand(18000, 22000));
                            break;

                        default: break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_sudsy_brew_alemental_AI(creature);
        }
};

// Pool of Suds 56748.
class npc_pool_of_suds : public CreatureScript
{
    public :
        npc_pool_of_suds() : CreatureScript("npc_pool_of_suds") { }

        struct npc_pool_of_suds_AI : public ScriptedAI
        {
            npc_pool_of_suds_AI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;

            void IsSummonedBy(Unit* /*summoner*/)
            {
                Reset();
            }

            void Reset()
            {
                me->AddAura(AURA_SUDS, me);
                me->SetReactState(REACT_PASSIVE);
            }

            void UpdateAI(const uint32 diff) { } // No melee.
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_pool_of_suds_AI(creature);
        }
};

// Unruly Alemental 56684.
class npc_unruly_alemental : public CreatureScript
{
    public :
        npc_unruly_alemental() : CreatureScript("npc_unruly_alemental") { }

        struct npc_unruly_alemental_AI : public ScriptedAI
        {
            npc_unruly_alemental_AI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;

            void InitializeAI()
            {
                if (!me->IsDead())
                    Reset();
            }

            void Reset()
            {
                events.Reset();

                if (!me->HasAura(SPELL_BREWHAHA))
                    me->AddAura(SPELL_BREWHAHA, me);
            }

            void EnterCombat(Unit* /*who*/)
            {
                events.ScheduleEvent(EVENT_BREW_BOLT3, urand(2000, 6000));
            }

            void EnterEvadeMode()
            {
                Reset();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->GetMotionMaster()->MoveTargetedHome();
            }

            void JustReachedHome()
            {
                if (!me->HasAura(SPELL_BREWHAHA))
                    me->AddAura(SPELL_BREWHAHA, me);
            }

            void UpdateAI(uint32 const diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_BREW_BOLT3:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                DoCast(target, SPELL_BREW_BOLT3);
                            events.ScheduleEvent(EVENT_BREW_BOLT3, urand(7000, 11000));
                            break;

                        default: break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_unruly_alemental_AI(creature);
        }
};

// Fizzy Brew Alemental 59520.
class npc_fizzy_brew_alemental : public CreatureScript
{
    public :
        npc_fizzy_brew_alemental() : CreatureScript("npc_fizzy_brew_alemental") { }

        struct npc_fizzy_brew_alemental_AI : public ScriptedAI
        {
            npc_fizzy_brew_alemental_AI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;

            void InitializeAI()
            {
                if (!me->IsDead())
                    Reset();
            }

            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit* /*who*/)
            {
                events.ScheduleEvent(EVENT_BREW_BOLT2, urand(2000, 6000));
                events.ScheduleEvent(EVENT_CARBONATION, urand(9000, 12000));
            }

            void EnterEvadeMode()
            {
                Reset();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->GetMotionMaster()->MoveTargetedHome();
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_BREW_BOLT2:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                DoCast(target, SPELL_BREW_BOLT2);
                            events.ScheduleEvent(EVENT_BREW_BOLT2, urand(7000, 11000));
                            break;

                        case EVENT_CARBONATION:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                DoCast(target, SPELL_CARBONATION_M);
                            events.ScheduleEvent(EVENT_CARBONATION, urand(22000, 26000));
                            break;

                        default: break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_fizzy_brew_alemental_AI(creature);
        }
};

// Pool of Carbonation 56746.
class npc_pool_of_carbonation : public CreatureScript
{
    public :
        npc_pool_of_carbonation() : CreatureScript("npc_pool_of_carbonation") { }

        struct npc_pool_of_carbonation_AI : public ScriptedAI
        {
            npc_pool_of_carbonation_AI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;

            void IsSummonedBy(Unit* /*summoner*/)
            {
                Reset();
            }

            void Reset()
            {
                me->AddAura(AURA_CARBONATION, me);
                me->SetReactState(REACT_PASSIVE);
            }

            void UpdateAI(uint32 const diff) { } // No melee.
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_pool_of_carbonation_AI(creature);
        }
};

// Bloated Brew Alemental 59518.
class npc_bloated_brew_alemental : public CreatureScript
{
    public :
        npc_bloated_brew_alemental() : CreatureScript("npc_bloated_brew_alemental") { }

        struct npc_bloated_brew_alemental_AI : public ScriptedAI
        {
            npc_bloated_brew_alemental_AI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;

            void InitializeAI()
            {
                if (!me->IsDead())
                    Reset();
            }

            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit* /*who*/)
            {
                events.ScheduleEvent(EVENT_BREW_BOLT, urand(2000, 6000));
                events.ScheduleEvent(EVENT_BLOAT, urand(10000, 14000));
            }

            void EnterEvadeMode()
            {
                Reset();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->GetMotionMaster()->MoveTargetedHome();
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_BREW_BOLT:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                DoCast(target, SPELL_BREW_BOLT);
                            events.ScheduleEvent(EVENT_BREW_BOLT, urand(7000, 11000));
                            break;

                        case EVENT_BLOAT:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                DoCast(target, SPELL_BLOAT);
                            events.ScheduleEvent(EVENT_BLOAT, urand(32000, 37000));
                            break;

                        default: break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_bloated_brew_alemental_AI(creature);
        }
};

// Bubbling Brew Alemental 59521.
class npc_bubbling_brew_alemental : public CreatureScript
{
    public :
        npc_bubbling_brew_alemental() : CreatureScript("npc_bubbling_brew_alemental") { }

        struct npc_bubbling_brew_alemental_AI : public ScriptedAI
        {
            npc_bubbling_brew_alemental_AI(Creature* creature) : ScriptedAI(creature), summons(me)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;
            SummonList summons;

            void InitializeAI()
            {
                if (!me->IsDead())
                    Reset();
            }

            void Reset()
            {
                events.Reset();
                summons.DespawnAll();
            }

            void EnterCombat(Unit* /*who*/)
            {
                events.ScheduleEvent(EVENT_BREW_BOLT4, urand(2000, 6000));
                events.ScheduleEvent(EVENT_BUBBLE_SHIELD, urand(9000, 17000));
            }

            void EnterEvadeMode()
            {
                Reset();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->GetMotionMaster()->MoveTargetedHome();
            }

            void JustDied(Unit* /*killer*/)
            {
                summons.DespawnAll();
            }

            void JustSummoned(Creature* summon)
            {
                summons.Summon(summon);
                summon->setActive(true);

		        if (me->isInCombat())
                    summon->SetInCombatWithZone();

                if (summon->GetEntry() == NPC_BUBBLE_SHIELD_TRASH)
                {
                    summon->SetReactState(REACT_PASSIVE);
                    summon->AddAura(SPELL_BUBBLE_SHIELD, me);
                }
            }

            void SummonedCreatureDies(Creature* summon, Unit* /*killer*/)
            {
                summons.Despawn(summon);

				if (AuraPtr aura = me->GetAura(SPELL_BUBBLE_SHIELD))
                {
                    if (aura->GetStackAmount() > 1)
                        me->SetAuraStack(SPELL_BUBBLE_SHIELD, me, aura->GetStackAmount() - 1);
                    else
                        me->RemoveAurasDueToSpell(SPELL_BUBBLE_SHIELD);
                }
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_BREW_BOLT4:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                DoCast(target, SPELL_BREW_BOLT4);
                            events.ScheduleEvent(EVENT_BREW_BOLT4, urand(7000, 11000));
                            break;

                        case EVENT_BUBBLE_SHIELD:
                            for (uint8 i = 0; i < 4; i++)
                                me->SummonCreature(NPC_BUBBLE_SHIELD_TRASH, me->GetPositionX() + frand(3.0f, -3.0f), me->GetPositionX() + frand(3.0f, -3.0f), me->GetPositionZ() + 0.1f, 0, TEMPSUMMON_MANUAL_DESPAWN);
                            events.ScheduleEvent(EVENT_BUBBLE_SHIELD, urand(42000, 54000));
                            break;

                        default: break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_bubbling_brew_alemental_AI(creature);
        }
};

// Yeasty Brew Alemental 59494.
class npc_yeasty_brew_alemental : public CreatureScript
{
    public :
        npc_yeasty_brew_alemental() : CreatureScript("npc_yeasty_brew_alemental") { }

        struct npc_yeasty_brew_alemental_AI : public ScriptedAI
        {
            npc_yeasty_brew_alemental_AI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;

            void InitializeAI()
            {
                if (!me->IsDead())
                    Reset();
            }

            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit* /*who*/)
            {
                events.ScheduleEvent(EVENT_BREW_BOLT4, urand(2000, 6000));
            }

            void EnterEvadeMode()
            {
                Reset();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->GetMotionMaster()->MoveTargetedHome();
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_BREW_BOLT4:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                DoCast(target, SPELL_BREW_BOLT4);
                            events.ScheduleEvent(EVENT_BREW_BOLT4, urand(7000, 11000));
                            break;

                        default: break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_yeasty_brew_alemental_AI(creature);
        }
};

// Leaking beer barrel 73186.
class npc_leaking_beer_barrel : public CreatureScript
{
    public :
        npc_leaking_beer_barrel() : CreatureScript("npc_leaking_beer_barrel") { }

        struct npc_leaking_beer_barrel_AI : public ScriptedAI
        {
            npc_leaking_beer_barrel_AI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;

            void InitializeAI()
            {
                if (!me->IsDead())
                    Reset();
            }

            void Reset()
            {
                if (Creature* beerBunny = me->FindNearestCreature(NPC_BEER_BARREL_BUNNY, 15.0f, true))
                    DoCast(beerBunny, SPELL_GUSHING_BREW_BVIS);
            }

            void UpdateAI(const uint32 diff) { }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_leaking_beer_barrel_AI(creature);
        }
};

// Beer barrel bunny 66215.
class npc_beer_barrel_bunny : public CreatureScript
{
    public :
        npc_beer_barrel_bunny() : CreatureScript("npc_beer_barrel_bunny") { }

        struct npc_beer_barrel_bunny_AI : public ScriptedAI
        {
            npc_beer_barrel_bunny_AI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;

            void InitializeAI()
            {
                if (!me->IsDead())
                    Reset();
            }

            void Reset()
            {
                me->AddAura(SPELL_GUSHING_BREW_A, me);
            }

            void UpdateAI(const uint32 diff) { }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_beer_barrel_bunny_AI(creature);
        }
};

// Spicy Explosion 107205, triggered by SPELL_PROC_EXPLOSION.
class spell_stormstout_brewery_habanero_beer : public SpellScriptLoader
{
    public:
        spell_stormstout_brewery_habanero_beer() : SpellScriptLoader("spell_stormstout_brewery_habanero_beer") { }

        class spell_stormstout_brewery_habanero_beer_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_stormstout_brewery_habanero_beer_SpellScript);

            void HandleInstaKill(SpellEffIndex /*effIndex*/)
            {
                if (!GetCaster())
                    return;

                std::list<Creature*> creatureList;
                GetCreatureListWithEntryInGrid(creatureList, GetCaster(), NPC_HABANERO_BREW, 10.0f);

                GetCaster()->RemoveAurasDueToSpell(SPELL_PROC_EXPLOSION);

                for (std::list<Creature*>::iterator barrel = creatureList.begin(); barrel != creatureList.end(); barrel++)
                {
                    if ((*barrel)->HasAura(SPELL_PROC_EXPLOSION))
                    {
                        (*barrel)->RemoveAurasDueToSpell(SPELL_PROC_EXPLOSION);
                        (*barrel)->CastSpell(*barrel, SPELL_SPICY_EXPLOSION, true);
                    }
                }
            }

            void HandleAfterCast()
            {
                if (Unit* caster = GetCaster())
                    if (caster->ToCreature())
                        caster->ToCreature()->DespawnOrUnsummon(1000);
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_stormstout_brewery_habanero_beer_SpellScript::HandleInstaKill, EFFECT_1, SPELL_EFFECT_INSTAKILL);
                AfterCast += SpellCastFn(spell_stormstout_brewery_habanero_beer_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_stormstout_brewery_habanero_beer_SpellScript();
        }
};

void AddSC_stormstout_brewery()
{
    new at_stormstout_brewery_entrance();
    new npc_chen_stormstout_entrance();
    new npc_ancestral_brewmaster();
    new npc_sodden_hozen_brawler();
    new npc_inflamed_hozen_brawler();
    new npc_hozen_bouncer();
    new npc_drunken_sleepy_hozen_brawler();
    new npc_stout_brew_alemental();
    new npc_sudsy_brew_alemental();
    new npc_pool_of_suds();
    new npc_unruly_alemental();
    new npc_fizzy_brew_alemental();
    new npc_pool_of_carbonation();
    new npc_bloated_brew_alemental();
    new npc_bubbling_brew_alemental();
    new npc_yeasty_brew_alemental();
    new npc_leaking_beer_barrel();
    new npc_beer_barrel_bunny();
    new spell_stormstout_brewery_habanero_beer();
}
