#include "CowRobot.h"
#include "CowBase.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/RobotController.h>
#include <frc/filter/LinearFilter.h>

CowRobot::CowRobot()
{
    m_DSUpdateCount = 0;

    m_Controller = NULL;

    // Set up drive motors
    m_LeftDriveA = new CowLib::CowMotorController(DRIVE_LEFT_A);
    m_LeftDriveB = new CowLib::CowMotorController(DRIVE_LEFT_B);
    m_LeftDriveA->SetStatorLimit(CONSTANT("STATOR_LIMIT"), CONSTANT("STATOR_THRESHOLD"), CONSTANT("STATOR_DURATION"));
    m_LeftDriveB->SetStatorLimit(CONSTANT("STATOR_LIMIT"), CONSTANT("STATOR_THRESHOLD"), CONSTANT("STATOR_DURATION"));

    m_RightDriveA = new CowLib::CowMotorController(DRIVE_RIGHT_A);
    m_RightDriveB = new CowLib::CowMotorController(DRIVE_RIGHT_B);
    m_RightDriveA->SetStatorLimit(CONSTANT("STATOR_LIMIT"), CONSTANT("STATOR_THRESHOLD"), CONSTANT("STATOR_DURATION"));
    m_RightDriveB->SetStatorLimit(CONSTANT("STATOR_LIMIT"), CONSTANT("STATOR_THRESHOLD"), CONSTANT("STATOR_DURATION"));

    m_IntakeF = new Intake(7, 5, 1, -1);
    m_IntakeR = new Intake(8, 6, 0, 1);

    m_Conveyor = new Conveyor(9, 10, 16, MXP_QEI_1_A);

    m_Shooter = new Shooter(11, 13, 12, 14);

    // not final IDs
    m_Climber = new Climber(18, 17);

    m_Limelight = new Limelight("limelight-front");

    m_LeftDriveA->SetNeutralMode(CowLib::CowMotorController::COAST);
    m_LeftDriveB->SetNeutralMode(CowLib::CowMotorController::COAST);

    m_RightDriveA->SetNeutralMode(CowLib::CowMotorController::COAST);
    m_RightDriveB->SetNeutralMode(CowLib::CowMotorController::COAST);

    m_MatchTime = 0;
    m_StartTime = 0;

    m_LEDDisplay = new CowLib::CowAlphaNum(0x70);

    m_Gyro = CowLib::CowGyro::GetInstance();

    // m_Gyro->Reset();
    m_PowerDistributionPanel = new frc::PowerDistribution();

    // m_Canifier = new CowLib::CowCanifier(15);

    m_LeftDriveValue = 0;
    m_RightDriveValue = 0;

    m_PreviousGyroError = 0;
    m_PreviousDriveError = 0;

    m_Accelerometer = new frc::BuiltInAccelerometer(frc::Accelerometer::kRange_4G);

    m_AccelY_LPF = new CowLib::CowLPF(CONSTANT("TIP_LPF"));
    m_TipTime = 0;
    m_Tipping = false;

    std::cout << "Set position: " << GetShooter()->GetSetpointH() << " Hood position: " << GetShooter()->GetHoodPosition() << std::endl;
}

void CowRobot::Reset()
{
    ResetEncoders();

    m_PreviousGyroError = 0;
    m_PreviousDriveError = 0;

    m_LeftDriveValue = 0;
    m_RightDriveValue = 0;
    m_MatchTime = 0;
    // m_AccelY_LPF->UpdateBeta(CONSTANT("TIP_LPF"));
    m_Shooter->ResetConstants();
    m_Climber->ResetConstants();

    m_ZFilter.Reset();
    m_PrevZ = 0;

    m_OverrideShooter = false;
}

void CowRobot::SetController(GenericController *controller)
{
    m_Controller = controller;
}

void CowRobot::PrintToDS()
{
    if (m_DSUpdateCount % 10 == 0)
    {
        m_DSUpdateCount = 0;
    }
}

// Used to handle the recurring logic funtions inside the robot.
// Please call this once per update cycle.
void CowRobot::handle()
{
    m_MatchTime = CowLib::CowTimer::GetFPGATimestamp() - m_StartTime;

    if (m_Controller == NULL)
    {
        printf("No controller for CowRobot!!\n");
        return;
    }

    // printf("Handling...\n");
    m_Controller->handle(this);

    // Default drive
    float tmpLeftMotor = m_LeftDriveValue;
    float tmpRightMotor = m_RightDriveValue;

    SetLeftMotors(tmpLeftMotor);
    SetRightMotors(tmpRightMotor);

    // accelerometers
    double zVal = m_ZFilter.Calculate(m_Accelerometer->GetZ());
    
    // positive is true, negative is false
    bool direction = (zVal - m_PrevZ) > 0? true : false;

    m_PrevZ = zVal;

    if (m_DSUpdateCount % 10 == 0)
    {
        // std::cout << "acc X: " << m_Accelerometer->GetX() << "\t\tacc Y: " << m_Accelerometer->GetY() << "\t\tacc Z: " << m_Accelerometer->GetZ() << std::endl;
        std::cout << "angle: " << 90 - (zVal * 90) << std::endl;
        if (direction)
        {
            std::cout << "moving positive" << std::endl;
        }
        else
        {
            std::cout << "moving negative" << std::endl;
        }
        // std::cout << "LEFT    Setpoint: " << GetClimber()->GetLeftSetpoint() << "  Position: " << GetClimber()->GetLeftPosition() << "\n";
        // std::cout << "RIGHT   Setpoint: " << GetClimber()->GetRightSetpoint() << "  Position: " << GetClimber()->GetRightPosition() << "\n\n";
        // std::cout << "Heading: " << m_Gyro->GetAngle() << "  Drive Distance: " << GetDriveDistance() << std::endl;
        // std::cout << "intake mode: " << m_IntakeModeR << std::endl;
        // std::cout << "conveyor mode: " << m_ConveyorMode << std::endl;
        // std::cout << "shooter F: " << GetShooter()->GetSpeedF() << std::endl;
        // std::cout << "comparator: " << fabs(GetShooter()->GetSpeedF() - GetShooter()->GetSetpointF()) << std::endl;
        // std::cout << "SHOOTER: Set speed: " << GetShooter()->GetSetpointF() << " Real speed: " << GetShooter()->GetSpeedF() << std::endl;
        // std::cout << "ROLLER: Set speed: " << GetShooter()->GetSetpointR() << " Real speed: " << GetShooter()->GetSpeedRoller() << std::endl;
        // std::cout << "HOOD: Set position: " << GetShooter()->GetSetpointH() << " Hood position: " << GetShooter()->GetHoodPosition() << std::endl;

        // 5 is drive
        // 4 s1
        // 3 s2
        // 2 arm
        // 1 unused

        // std::cout << "gyro: " <<  m_Gyro->GetAngle() << std::endl;
        // std::cout << std::dec
        //           << m_DriveEncoder->Get() << " "
        //       << m_Gyro->GetAngle() << std::endl;std::cout << "Heading: " << m_Gyro->GetAngle() << " " << m_DriveEncoder->GetDistance() << std::endl;
        // std::cout << "drive distance: " << GetDriveDistance() << std::endl;
        // std::cout << "match time (ours): " << m_MatchTime << std::endl;
    }

    // frc::SmartDashboard::PutNumber("Drive Distance", GetDriveDistance());
    // frc::SmartDashboard::PutNumber("Shooter", GetShooter()->GetSpeedF());
    // frc::SmartDashboard::PutBoolean("Front Intake Deployed", GetIntakeF()->GetExtended());
    // frc::SmartDashboard::PutBoolean("Rear Intake Deployed", GetIntakeR()->GetExtended());

    // m_LogServer->RemoteLog(m_Shooter->GetSpeedF());

    m_IntakeF->handle();
    m_IntakeR->handle();
    m_Conveyor->handle();
    m_Shooter->handle();
    m_Climber->handle();
    // m_Canifier->Handle();

    m_DSUpdateCount++;
}

void CowRobot::SetConveyorMode(ConveyorMode newMode, bool rear, double percentage)
{   
    // Only changes the conveyor mode if the new mode is higher priority
    if (m_ConveyorMode < newMode)
    {
        m_ConveyorMode = newMode;
    }

    double percentFront, percentRear;
    percentFront  = percentage;
    percentRear = percentage;

    if (rear)
    {
        percentFront = 0.25;
    }
    else
    {
        percentRear = 0.25;
    }

    // int freq = m_Conveyor->GetColorSensor()->GetFrequency();

    switch (m_ConveyorMode)
    {
    case CONVEYOR_OFF:
        GetConveyor()->SetSpeed(0, 0, 0);
        break;
    case CONVEYOR_EXHAUST:
        // std::cout << "exhaust, percentFront: " << percentFront << "  precentRear: " << percentRear << std::endl;
        GetConveyor()->SetSpeed(-CONSTANT("CONVEYOR_OUT_UP") * percentage, -CONSTANT("CONVEYOR_OUT_LOW") * percentFront, -CONSTANT("CONVEYOR_OUT_LOW") * percentRear);
        break;
    case CONVEYOR_INTAKE:
        GetConveyor()->SetSpeed(CONSTANT("CONVEYOR_IN_UP") * percentage, CONSTANT("CONVEYOR_IN_LOW") * percentage, CONSTANT("CONVEYOR_IN_LOW") * percentage);
        break;
    case CONVEYOR_SHOOT:
        GetConveyor()->SetSpeed(CONSTANT("CONVEYOR_SHOOT_UP") * percentage, CONSTANT("CONVEYOR_SHOOT_LOW") * percentage, CONSTANT("CONVEYOR_SHOOT_LOW") * percentage);
        break;
    }
}

void CowRobot::SetIntakeMode(IntakeMode newMode, bool rear, double percentage)
{
    // Creates pointers to the intake and intake mode coresponding to the selected side
    Intake *intake = NULL;
    IntakeMode *intakeMode = NULL;

    if (rear)
    {
        intake = GetIntakeR();
        intakeMode = &m_IntakeModeR;
    }
    else
    {
        intake = GetIntakeF();
        intakeMode = &m_IntakeModeF;
    }

    // Only changes the intake mode if the new mode is higher priority
    if (*intakeMode < newMode)
    {
        *intakeMode = newMode;
    }

    switch (*intakeMode)
    {
    case INTAKE_OFF:
        intake->SetSpeed(0, 0);
        break;
    case INTAKE_EXHAUST:
        intake->SetSpeed(-CONSTANT("INTAKE_ON") * percentage, -CONSTANT("INDEXER_ON") * percentage);
        break;
    case INTAKE_SHOOT:
        intake->SetSpeed(0, 0);
        break;
    case INTAKE_INTAKE:
        intake->SetSpeed(CONSTANT("INTAKE_ON") * percentage, CONSTANT("INDEXER_ON") * percentage);
        break;
    }
}

void CowRobot::ShootBalls()
{
    // std::cout << "shooter F: " << GetShooter()->GetSpeedF() << std::endl;
    // std::cout << "comparator: " << fabs(GetShooter()->GetSpeedF() - GetShooter()->GetSetpointF()) << std::endl;

    SetConveyorMode(CONVEYOR_SHOOT, false);
    SetIntakeMode(INTAKE_SHOOT, false);
    SetIntakeMode(INTAKE_SHOOT, true);

    // if (GetShooter()->GetSetpointH() == CONSTANT("HOOD_DOWN"))
    // {
    //     GetShooter()->SetHoodRollerSpeed(CONSTANT("HOOD_ROLLER_SPEED_DOWN"));
    // }
    // else if (GetShooter()->GetSetpointH() == CONSTANT("HOOD_UP"))
    // {
    //     GetShooter()->SetHoodRollerSpeed(CONSTANT("HOOD_ROLLER_SPEED_UP"));
    // }
    // else
    // {
    //     GetShooter()->SetHoodRollerSpeed(CONSTANT("HOOD_ROLLER_SPEED_UP"));
    // }
}

void CowRobot::RunShooter()
{
    float setpoint = GetShooter()->GetSetpointH();
    
    // this is here twice because having no target will use this case
    if (setpoint == CONSTANT("HOOD_FENDER"))
    {
        GetShooter()->SetSpeed(CONSTANT("SHOOTER_SPEED_FENDER"));
        GetShooter()->SetHoodRollerSpeed(CONSTANT("HOOD_ROLLER_SPEED_FENDER"));
        return;
    }

    if (m_OverrideShooter)
    {
        if (setpoint == CONSTANT("HOOD_LAUNCHPAD"))
        {
            GetShooter()->SetSpeed(CONSTANT("SHOOTER_SPEED_LAUNCHPAD"));
            GetShooter()->SetHoodRollerSpeed(CONSTANT("HOOD_ROLLER_SPEED_LAUNCHPAD"));
        }
        else if (setpoint == CONSTANT("HOOD_FENDER"))
        {
            GetShooter()->SetSpeed(CONSTANT("SHOOTER_SPEED_FENDER"));
            GetShooter()->SetHoodRollerSpeed(CONSTANT("HOOD_ROLLER_SPEED_FENDER"));
        }
        return;
    }
    
    // 1 is max speed, 0 is lowest
    float hoodPercent = (setpoint - CONSTANT("TARGET_Y_CLOSE")) / (CONSTANT("TARGET_Y_FAR") - CONSTANT("TARGET_Y_CLOSE"));

    float shooterSpeed = (CONSTANT("SHOOTER_SPEED_UP") - CONSTANT("SHOOTER_SPEED_DOWN")) * hoodPercent + CONSTANT("SHOOTER_SPEED_DOWN");
    float rollerSpeed = (CONSTANT("HOOD_ROLLER_SPEED") - CONSTANT("HOOD_ROLLER_SPEED_DOWN")) * hoodPercent + CONSTANT("HOOD_ROLLER_SPEED_DOWN");

    if (hoodPercent >= CONSTANT("SHOOTER_C_MIN") && hoodPercent <= CONSTANT("SHOOTER_C_MAX"))
    {
        shooterSpeed *= CONSTANT("SHOOTER_C");
        rollerSpeed *= CONSTANT("SHOOTER_C");
    }

    GetShooter()->SetSpeed(shooterSpeed);
    GetShooter()->SetHoodRollerSpeed(rollerSpeed);
}

void CowRobot::ShooterOverride(bool override)
{
    m_OverrideShooter = override;
}

bool CowRobot::DoVisionTracking(float speed, float threshold)
{
    float pid = m_Limelight->CalcNewPid();

    DriveSpeedTurn(speed, pid, true);

    if (fabs(m_Limelight->GetTargetXPos()) <= threshold)
    {
        return true;
    }

    return false;

    // Limelight has valid targets
    // if (GetLimelight()->GetNumber("tv", 0) == 1)
    // {
    //     // If the target area is larger than the threshold, we likely have the gamepiece or scored
    //     if (GetLimelight()->GetNumber("ta", 0) >= threshold)
    //     {
    //         return true;
    //     }
    //     return false;
    // }
}

double CowRobot::GetDriveDistance()
{
    float direction = -1.0;
    float position = 0;
    if (m_LeftDriveA)
    {
        // position / falcon units per rev * gear ratio
        position = m_LeftDriveA->GetPosition() / (2048 * (46 / 12));
        position *= 12.56636;
        position *= direction;
    }
    return position;
}

// void CowRobot::DriveSpeedPushDistance()
// {
//     double distDelta = GetDriveDistance() - m_PrevDist;
//     m_PrevDist = distDelta + m_PrevDist;

//     m_DistDeltaBuff[m_DistIdx++] = distDelta;
// }

// double CowRobot::GetDriveSpeed()
// {
//     // make sure to change this if we increase number of values in buffer
//     int buffSize = 20;

//     double sum = 0.0;
//     for (int i = 0; i < buffSize; i++)
//     {
//         sum += m_DistDeltaBuff[i];
//     }

//     return sum / buffSize;
// }

bool CowRobot::DriveDistance(double distance)
{
    double PID_P = CONSTANT("DRIVE_P");
    double PID_D = CONSTANT("DRIVE_D");
    double error = distance - GetDriveDistance();
    double dError = error - m_PreviousDriveError;
    double output = PID_P * error + PID_D * dError;

    double speed = CONSTANT("PTO_DRIVE_SPEED");
    DriveLeftRight(speed - output, speed + output);

    m_PreviousDriveError = error;

    return (fabs(error) < 4 && CowLib::UnitsPerSecond(fabs(dError)) < 1);
}

bool CowRobot::DriveDistanceWithHeading(double heading, double distance, double speed)
{
    double PID_P = CONSTANT("DRIVE_P");
    double PID_D = CONSTANT("DRIVE_D");
    double error = distance - GetDriveDistance();
    double dError = error - m_PreviousDriveError;
    double output = PID_P * error + PID_D * dError;

    double throttle = CowLib::LimitMix(output, speed);
    // throttle *= -1;
    // std::cout << "Drive request speed: " << throttle << std::endl;

    bool headingResult = DriveWithHeading(heading, throttle);

    m_PreviousDriveError = error;

    return (fabs(error) < 4 && headingResult);
}

bool CowRobot::TurnToHeading(double heading)
{
    double PID_P = CONSTANT("TURN_P");
    double PID_D = CONSTANT("TURN_D");
    double error = m_Gyro->GetAngle() - heading;
    double dError = error - m_PreviousGyroError;
    double output = PID_P * error + PID_D * dError;

    // speed *= -speed;

    DriveLeftRight(-output, output);

    m_PreviousGyroError = error;

    return (fabs(error) < 1 && CowLib::UnitsPerSecond(fabs(dError)) < 0.5);
}

bool CowRobot::DriveWithHeading(double heading, double speed)
{
    double PID_P = CONSTANT("TURN_P");
    double PID_D = CONSTANT("TURN_D");
    double error = m_Gyro->GetAngle() - heading;
    double dError = error - m_PreviousGyroError;
    double output = PID_P * error + PID_D * dError;

    // speed *= -speed;

    DriveLeftRight(speed - output, speed + output);

    m_PreviousGyroError = error;

    return (fabs(error) < 1 && CowLib::UnitsPerSecond(fabs(dError)) < 0.5);
}

bool CowRobot::DriveWithHeading(double heading, double speed, double maxSpeed)
{
    double PID_P = CONSTANT("TURN_P");
    double PID_D = CONSTANT("TURN_D");
    double error = heading - m_Gyro->GetAngle();
    double dError = error - m_PreviousGyroError;
    double output = PID_P * error + PID_D * dError;
    output = CowLib::LimitMix(output, maxSpeed);

    DriveLeftRight(speed + output, speed - output);

    m_PreviousGyroError = error;

    return (fabs(error) < 1 && CowLib::UnitsPerSecond(fabs(dError)) < 0.5);
}

// Allows skid steer robot to be driven using tank drive style inputs
void CowRobot::DriveLeftRight(float leftDriveValue, float rightDriveValue)
{
    m_LeftDriveValue = -leftDriveValue;
    m_RightDriveValue = -rightDriveValue;
}

void CowRobot::DriveSpeedTurn(float speed, float turn, bool quickTurn)
{
    // Linear degredation of steeering based off of velocity

    // velocity *= 0.003;
    float temp_vel = speed;
    float sensitivity = 0;

    if (temp_vel < 0)
        temp_vel = -temp_vel;

    // printf("Velocity: %f, stick: %f\r\n", velocity, temp_vel);

    if (speed < 0.10 && speed > -0.10)
        speed = 0;
    if (((turn < 0.02) && (turn > -0.02)) || ((speed == 0) && !quickTurn))
        turn = 0;

    if (quickTurn)
    {
        if (speed == 0.0)
        {
            sensitivity = 1;
        }
        else
        {
            sensitivity = CONSTANT("STEERING_QUICKTURN");
        }
    }
    else
    {
        sensitivity = CONSTANT("STEERING_NOQUICKTURN");
    }

    turn *= sensitivity;
    // turn = -turn;

    float left_power = CowLib::LimitMix(speed - turn);
    float right_power = CowLib::LimitMix(speed + turn);

    DriveLeftRight(left_power, right_power);
}

// Allows robot to spin in place
void CowRobot::QuickTurn(float turnRate)
{
    // When provided with + turn, quick turn right

    float left = -1 * turnRate;
    float right = turnRate;

    DriveLeftRight(left, right);
}

// Sets the left side motors
void CowRobot::SetLeftMotors(float val)
{
    if (val > 1.0)
        val = 1.0;
    if (val < -1.0)
        val = -1.0;

    m_LeftDriveA->Set(val);
    m_LeftDriveB->Set(val);
}

// Sets the left side motors
void CowRobot::SetRightMotors(float val)
{
    if (val > 1.0)
        val = 1.0;
    if (val < -1.0)
        val = -1.0;

    m_RightDriveA->Set(-val);
    m_RightDriveB->Set(-val);
}

void CowRobot::StartTime()
{
    m_StartTime = CowLib::CowTimer::GetFPGATimestamp();
}
