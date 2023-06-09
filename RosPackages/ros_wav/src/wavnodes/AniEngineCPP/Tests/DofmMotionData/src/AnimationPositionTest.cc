#include "DB_Local_Store.h"
#include "DataTypes/Expressions_Type.h"
#include "nlohmann/json.hpp"

#include "AnimationPositions.h"
#include "AnimationObject.h"

#include "AnimationPositionTest.h"

using jsonObject = nlohmann::json;

using namespace fmDB;
using namespace fmMotionData;

AnimationPositionTest::AnimationPositionTest()
{

}

TEST_F(AnimationPositionTest, AnimationPositionTest) {

    DB_Local_Store mDB_Local_Store;
    Expressions_Type expression = mDB_Local_Store.readExpression("Stand_Straight");
    printf("%s", expression.Action_Data.c_str());

    AnimationPositions animationPosition;
     
    jsonObject jPosition = jsonObject::parse(expression.Action_Data);

    animationPosition.parseJson(jPosition);
    EXPECT_EQ(animationPosition.volume, 0.2);
    EXPECT_EQ(static_cast<ImageAnimationTransition*>(animationPosition.Transition.TransitionSet.at(AnimationObject::Image_EyeBrowRight).get())->Identity, ImageAnimationTransition::Identity);
    EXPECT_EQ(static_cast<ImageAnimationTransition*>(animationPosition.Transition.TransitionSet.at(AnimationObject::Image_EyeBrowRight).get())->Duration, 1500);
    EXPECT_EQ(static_cast<ImageAnimationTransition*>(animationPosition.Transition.TransitionSet.at(AnimationObject::Image_EyeBrowRight).get())->Delay, 0.0);
    EXPECT_EQ(static_cast<ImageAnimationTransition*>(animationPosition.Transition.TransitionSet.at(AnimationObject::Image_EyeBrowRight).get())->Damping, 0.0);
    EXPECT_EQ(static_cast<ImageAnimationTransition*>(animationPosition.Transition.TransitionSet.at(AnimationObject::Image_EyeBrowRight).get())->Amplitude, 0.0);



    EXPECT_EQ(get<0>(static_cast<ImageAnimationState*>(animationPosition.State.StateSet.at(AnimationObject::Image_EyeBrowRight).get())->Matrix.a), 0.808638);
    EXPECT_EQ(get<0>(static_cast<ImageAnimationState*>(animationPosition.State.StateSet.at(AnimationObject::Image_EyeBrowRight).get())->Matrix.b), -0.588305);
    EXPECT_EQ(get<0>(static_cast<ImageAnimationState*>(animationPosition.State.StateSet.at(AnimationObject::Image_EyeBrowRight).get())->Matrix.c), 0.588305);
    EXPECT_EQ(get<0>(static_cast<ImageAnimationState*>(animationPosition.State.StateSet.at(AnimationObject::Image_EyeBrowRight).get())->Matrix.d), 0.808638);
    EXPECT_EQ(get<0>(static_cast<ImageAnimationState*>(animationPosition.State.StateSet.at(AnimationObject::Image_EyeBrowRight).get())->Matrix.tx), -93.038796);
    EXPECT_EQ(get<0>(static_cast<ImageAnimationState*>(animationPosition.State.StateSet.at(AnimationObject::Image_EyeBrowRight).get())->Matrix.ty), 15.749040);
    EXPECT_EQ(get<0>(static_cast<ImageAnimationState*>(animationPosition.State.StateSet.at(AnimationObject::Image_EyeBrowRight).get())->opacity), 1.0);
    EXPECT_EQ(get<0>(static_cast<ImageAnimationState*>(animationPosition.State.StateSet.at(AnimationObject::Image_EyeBrowRight).get())->centreX), 0.0);
    EXPECT_EQ(get<0>(static_cast<ImageAnimationState*>(animationPosition.State.StateSet.at(AnimationObject::Image_EyeBrowRight).get())->centreY), 0.0);
    EXPECT_EQ(get<0>(static_cast<ImageAnimationState*>(animationPosition.State.StateSet.at(AnimationObject::Image_EyeBrowRight).get())->AnchorX), 0.0);
    EXPECT_EQ(get<0>(static_cast<ImageAnimationState*>(animationPosition.State.StateSet.at(AnimationObject::Image_EyeBrowRight).get())->AnchorY), 0.0);
    EXPECT_EQ(static_cast<ImageAnimationState*>(animationPosition.State.StateSet.at(AnimationObject::Image_EyeBrowRight).get())->AnimationKind, fmMotionData::AnimationTypes::Identity);

    

    EXPECT_EQ(get<0>(static_cast<MotorAnimationState*>(animationPosition.State.StateSet.at(AnimationObject::Motor_Lift).get())->Angle), -23);
    EXPECT_EQ(get<1>(static_cast<MotorAnimationState*>(animationPosition.State.StateSet.at(AnimationObject::Motor_Lift).get())->Angle), true);
    EXPECT_EQ(static_cast<MotorAnimationState*>(animationPosition.State.StateSet.at(AnimationObject::Motor_Lift).get())->IsDeltaAngle, true);


    EXPECT_EQ(static_cast<MotionAnimationTransition*>(animationPosition.Transition.TransitionSet.at(AnimationObject::Motor_Lift).get())->Timing, 1500);
    EXPECT_EQ(static_cast<MotionAnimationTransition*>(animationPosition.Transition.TransitionSet.at(AnimationObject::Motor_Lift).get())->Delay, 0);
    EXPECT_EQ(static_cast<MotionAnimationTransition*>(animationPosition.Transition.TransitionSet.at(AnimationObject::Motor_Lift).get())->Velocity, 0);
    EXPECT_EQ(static_cast<MotionAnimationTransition*>(animationPosition.Transition.TransitionSet.at(AnimationObject::Motor_Lift).get())->Frequency, 0);
    EXPECT_EQ(static_cast<MotionAnimationTransition*>(animationPosition.Transition.TransitionSet.at(AnimationObject::Motor_Lift).get())->Damp, 0);
    EXPECT_EQ(static_cast<MotionAnimationTransition*>(animationPosition.Transition.TransitionSet.at(AnimationObject::Motor_Lift).get())->EasingFunction, CommandLabels::EasingFunction::SIN);
    EXPECT_EQ(static_cast<MotionAnimationTransition*>(animationPosition.Transition.TransitionSet.at(AnimationObject::Motor_Lift).get())->EasingType, CommandLabels::EasingType::IN);

}

