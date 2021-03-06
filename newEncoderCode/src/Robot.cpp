#include <iostream>
#include <string>
#include "WPILib.h"
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include "ctre/Phoenix.h"
#include <Encoder.h>
#include <Joystick.h>
#include <DigitalInput.h>

class Robot : public frc::IterativeRobot {
	WPI_TalonSRX *srx = new WPI_TalonSRX(1);
/*	WPI_TalonSRX *srx1 = new WPI_TalonSRX(1);
	WPI_TalonSRX *srx2 = new WPI_TalonSRX(2);
	WPI_TalonSRX *srx3 = new WPI_TalonSRX(3); */

	frc::Talon motor2 {0};
private:
	frc::Joystick Stick { 0 };
	frc::DigitalInput limit { 9 };
public:

	//frc::PWMTalonSRX motor {0};


	void RobotInit(void) {


		m_chooser.AddDefault(kAutoNameDefault, kAutoNameDefault);
		m_chooser.AddObject(kAutoNameCustom, kAutoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &m_chooser);


		int absolutePosition = srx->GetSensorCollection().GetPulseWidthPosition() & 0xFFF;
		srx->GetSensorCollection().SetQuadraturePosition(absolutePosition,5);

		//srx->GetSensorCollection().set
		//srx->configs

	//	srx.SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative); /* MagEncoder meets the requirements for Unit-Scaling */
	//	srx.SetStatusFrameRateMs(CANTalon::StatusFrameRateFeedback, 5); /* Talon will send new frame every 5ms */
	//	srx->SetS
	}
	void AutonomousInit() override {
		m_autoSelected = m_chooser.GetSelected();
		// m_autoSelected = SmartDashboard::GetString(
		// 		"Auto Selector", kAutoNameDefault);
		std::cout << "Auto selected: " << m_autoSelected << std::endl;

		if (m_autoSelected == kAutoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}
	void AutonomousPeriodic(void) {
		if (m_autoSelected == kAutoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
		std::string gameData;
				gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
				if(gameData[0] == 'L')
				{

					frc::SmartDashboard::PutNumber("side",1);

				}
				else {

					frc::SmartDashboard::PutNumber("side",2);
				}

	}
	void TeleopInit() {}

	void TeleopPeriodic(void) {
				double selectvel = srx->GetSensorCollection().GetQuadratureVelocity();
				double selectpos = srx->GetSensorCollection().GetQuadraturePosition();
				bool btn1 = Stick.GetRawButtonPressed(1);

				if (btn1) {
					srx->GetSensorCollection().SetQuadraturePosition(0,4);
				}

				double limits = limit.Get();
				frc::SmartDashboard::PutNumber("limit switch", limits);

				if (limit.Get()) {
					motor2.Set(Stick.GetRawAxis(1));
				}
				if (!limit.Get()) {
					motor2.Set(0);
				}


				//if (Stick->GetRawButton(6)) {
				//	srx->Set(0);
				//}

				frc::SmartDashboard::PutNumber("Selected Encoder velocity", selectvel);
				frc::SmartDashboard::PutNumber("Selected Encoder Position", selectpos);
	}
private:
	frc::LiveWindow& m_lw = *LiveWindow::GetInstance();
	frc::SendableChooser<std::string> m_chooser;
	const std::string kAutoNameDefault = "Default";
	const std::string kAutoNameCustom = "My Auto";
	std::string m_autoSelected;
};

START_ROBOT_CLASS(Robot)
