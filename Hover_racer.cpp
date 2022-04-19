// Hover racer
// https://github.com/MozzH/Hover-Racer



#include <TL-Engine.h>// TL-Engine include file and namespace
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <math.h>
#include <cmath>

using namespace std;
using namespace tle;

#pragma region Data structures

/*=== Checkpoint properties ===*/
enum checkPointState { Unpassed, Passed }; //Enum to store states
struct CheckPoints
{
	IModel* checkPointModel;
	checkPointState state;

	void unpassed()
	{
		state = Unpassed;
	}

	void passed()
	{
		state = Passed;
	}

};

/*=== Dummy properties ===*/
enum DummyState { Attached, NotAttached }; //Enum to store states
struct DUMMIES
{
	IModel* dummyModel; //The model
	DummyState state; //The state of the dummy

					  //Setting the state of the dummy to "Attached"
	void setAttached()
	{
		state = Attached;
	}

	//Setting the state of the dummy to "NotAttached"
	void setNotAttached()
	{
		state = NotAttached;
	}
	/*===========================================================================================================\
	| reason i'm using a data structure for the dummy is so its easier to switch between camera modes & to detect|
	| collision so it can also distinguish whether or not the dummy is attached to something or not, explanation |
	| in report                                                                                                  |
	\===========================================================================================================*/
};

/*=== Car properties ===*/
enum CarController { Human, Robot };
enum CarState { Cool, Overheated };
struct CAR
{
	IModel* carModel;
	CarController state;
	CarState carState;
	int health;

	void controllerByHuman()
	{
		state = Human;
	}

	void controlledByComputer()
	{
		state = Robot;
	}

	void setCool()
	{
		carState = Cool;
	}

	void setOverheated()
	{
		carState = Overheated;
	}

	/*===========================================================================================================\
	| This enum + data structure was made to have individual stats of the health and state of each individual car|
	| and to distinguish whether the car is controlled by a human or not                                         |
	\===========================================================================================================*/

};

/*=== Game Stage properties ===*/
enum Game_Stage { Demo, Count_Down, Stage_0, Stage_1, Stage_2, Stage_3, Stage_4, Stage_5, Race_Complete, End_Race };
struct GAME_STAGE
{
	Game_Stage state;

	//Changing the state of the game accordingly
	void setDemo()
	{
		state = Demo;
	}

	void setCountDown()
	{
		state = Count_Down;
	}

	void setStage0()
	{
		state = Stage_0;
	}

	void setStage1()
	{
		state = Stage_1;
	}

	void setStage2()
	{
		state = Stage_2;
	}

	void setStage3()
	{
		state = Stage_3;
	}

	void setStage4()
	{
		state = Stage_4;
	}

	void setStage5()
	{
		state = Stage_5;
	}

	void completeRace()
	{
		state = Race_Complete;
	}

	void endRace()
	{
		state = End_Race;
	}
};

/*=== Camera properties ===*/
enum Camera_State { Free_Moving, First_Person, Third_Person, Surveillance };
struct CAMERA_STATE
{
	Camera_State state;

	//Changing camera states accordingly
	void setFreeMoving()
	{
		state = Free_Moving;
	}

	void setFirstPerson()
	{
		state = First_Person;
	}

	void setThirdPerson()
	{
		state = Third_Person;
	}

	void setSurveillance()
	{
		state = Surveillance;
	}
};
#pragma endregion

#pragma region Functions

void collisionDetectionWall(IMesh* carDestroy, IModel* wall, CAR &car, float &velocity, GAME_STAGE stage)
{
	//Delcaring all the variables before the process starts
	//Radius of entities
	const float wallRadius = 2.0f;
	const float carRadius = 4.0f;

	//Variables of entities
	float xWall, yWall, zWall; //Block XYZ
	float xCar, yCar, zCar; //Marble XYZ

							//Calculating max/min boundary +/- radius
	float xMaximum, yMaximum, zMaximum; //Maximum boundaries + radius XYZ
	float xMinimum, yMinimum, zMinimum; //Minimum boundaries - radius XYZ

										//wall coords <> Getting XYZ values of the entity
	xWall = wall->GetLocalX();
	yWall = wall->GetLocalY();
	zWall = wall->GetLocalZ();

	//car coords <> Getting XYZ values of the entity
	xCar = car.carModel->GetLocalX();
	yCar = car.carModel->GetLocalY();
	zCar = car.carModel->GetLocalZ();

	//max boundaries + radius <> Calculating XYZ values 
	xMaximum = xWall + wallRadius + carRadius;
	yMaximum = yWall + wallRadius + carRadius;
	zMaximum = zWall + wallRadius + carRadius;

	//min boundaries - radius <> Calculating XYZ values 
	xMinimum = xWall - wallRadius - carRadius;
	yMinimum = yWall - wallRadius - carRadius;
	zMinimum = zWall - wallRadius - carRadius;

	//main process <> where the magic happens
	if ((xCar > xMinimum && xCar < xMaximum) && (yCar > yMinimum && yCar < yMaximum) && (zCar > zMinimum && zCar < zMaximum))
	{
		if (car.health >= 1)
		{
			//Speeds will be rounded*
			//Decreasing the health of the car depending on the speed - As required by the assignment
			if (velocity >= 0.4875f) //rounded to = 48.75 = 75% of the speed
			{
				car.health -= 15; //-15HP if the speed is over 75%, which is 48.75
			}

			if (velocity >= 0.3250f && velocity <= 0.4875f) //50% of the speed
			{
				//-10HP if the speed is less than 75% and more than 50%, which is in the range of 32.50 and 48.75
				car.health -= 10;
			}

			if (velocity >= 0.1625f && velocity <= 0.3250f)
			{
				//-5HP if the speed is less than 50% and more than 25%, which is in the range of 16.25 and 32.50
				car.health -= 5;
			}

			/* Keep in mind that the maximum velocity is 65.0f, the calculations were based on that  */
		}

		//If the car is dead, then it will get removed
		if (car.health < 1)
		{
			carDestroy->RemoveModel(car.carModel); //Removing the model
			stage.endRace(); //Ending the race since the car is dead
		}

		velocity /= -2; //Bouncing back effect
	}
}

void collisionDetectionDummy(IMesh* dummyMesh, DUMMIES dummy, CAR &car, float &velocity)
{

	float boundary = 4.0;
	float radius = 2.0;

	//dummy on checkpoint coordinates
	float xDummy, yDummy, zDummy;
	xDummy = dummy.dummyModel->GetLocalX();
	yDummy = dummy.dummyModel->GetLocalY();
	zDummy = dummy.dummyModel->GetLocalZ();

	//car coordinates
	float xCar, yCar, zCar;
	xCar = car.carModel->GetLocalX();
	yCar = car.carModel->GetLocalY();
	zCar = car.carModel->GetLocalZ();

	//max boundaries + radius
	float xMax, yMax, zMax;
	xMax = xCar + boundary + radius;
	yMax = yCar + boundary + radius;
	zMax = zCar + boundary + radius;

	//min boundaries - radius
	float xMin, yMin, zMin;
	xMin = xCar - boundary - radius;
	yMin = yCar - boundary - radius;
	zMin = zCar - boundary - radius;

	if ((xDummy > xMin && xDummy < xMax) && (yDummy > yMin && yDummy < yMax) && (zDummy > zMin && zDummy < zMax))
	{
		velocity /= -2; //Bouncing back effect
	}
}

void passCheckPointCollision(CAR car, DUMMIES dummy, IMesh* crossMesh, vector<IModel*> cross, GAME_STAGE stage)
{
	float boundary = 10.0;
	float radius = 10.0;
	IModel* tempCrossModel;

	//dummy on checkpoint coordinates
	float xDummy, yDummy, zDummy;
	xDummy = dummy.dummyModel->GetLocalX();
	yDummy = dummy.dummyModel->GetLocalY();
	zDummy = dummy.dummyModel->GetLocalZ();

	//car coordinates
	float xCar, yCar, zCar;
	xCar = car.carModel->GetLocalX();
	yCar = car.carModel->GetLocalY();
	zCar = car.carModel->GetLocalZ();

	//max boundaries + radius
	float xMax, yMax, zMax;
	xMax = xCar + boundary + radius;
	yMax = yCar + boundary + radius;
	zMax = zCar + boundary + radius;

	//min boundaries - radius
	float xMin, yMin, zMin;
	xMin = xCar - boundary - radius;
	yMin = yCar - boundary - radius;
	zMin = zCar - boundary - radius;

	if ((xDummy > xMin && xDummy < xMax) && (yDummy > yMin && yDummy < yMax) && (zDummy > zMin && zDummy < zMax))
	{
		if (stage.state == Stage_0)
		{
			stage.setStage1();
		}

		else if (stage.state == Stage_1)
		{
			stage.setStage2();
		}

		else if (stage.state == Stage_2)
		{
			stage.setStage3();
		}

		else if (stage.state == Stage_3)
		{
			stage.setStage4();
		}


		else if (stage.state == Stage_4)
		{
			stage.setStage5();
		}


		else if (stage.state == Stage_5)
		{
			stage.completeRace();
		}

		tempCrossModel = crossMesh->CreateModel(xDummy, yDummy, zDummy);
		cross.push_back(tempCrossModel);
	}
}

void spawnWalls(IMesh* wallMesh, vector<IModel*> &wallVec, IMesh* teeWall, vector<IModel*> tWalls)
{
	float zOfWalls1 = 560.0f; //Initial z position of inner wall(s)
	float xOfWalls1 = 640.0f; //Initial x position of inner wall(s)
	float zOfWalls2 = 740.0f; //Initial z position of outer wall(s)
	float xOfWalls2 = 760.0f; //Initial x position of outer wall(s)

	IModel* tempWallModel; //Temporary model
	IModel* tempTWallModel; //Temporary t wall model

#pragma region Inner walls
	for (int i = 0; i < 53; i++) //For loop that automatically renders the entities
	{
		//Function
		wallVec.push_back(tempWallModel = wallMesh->CreateModel(xOfWalls1, 3, -zOfWalls1)); //Adding to the vector 
		tempWallModel->Scale(2.0f);
		tempWallModel->SetSkin("conc02.jpg");
		zOfWalls1 -= 19.5f; //decrementing the value of x so they spawn with proper distance between them
	}

	//Turn
	tempTWallModel = teeWall->CreateModel(640, 3, -zOfWalls1);
	tempTWallModel->Scale(2.0f);
	tWalls.push_back(tempTWallModel);

	for (int i = 0; i < 49; i++) //For loop that automatically renders the entities
	{
		//Function
		wallVec.push_back(tempWallModel = wallMesh->CreateModel(xOfWalls1 - 10, 3, -zOfWalls1)); //Adding to the vector 
		tempWallModel->RotateY(90);
		tempWallModel->Scale(2.0f);
		tempWallModel->SetSkin("conc02.jpg");
		xOfWalls1 -= 19.5f; //decrementing the value of x so they spawn with proper distance between them
	}

	//Added one extra model here so it looks better
	//Turn
	wallVec.push_back(tempWallModel = wallMesh->CreateModel(xOfWalls1 - 10, 3, -zOfWalls1)); //Adding to the vector 
	tempWallModel->RotateY(90);
	tempWallModel->Scale(2.0f);
	tempWallModel->SetSkin("conc02.jpg");
	tempTWallModel = teeWall->CreateModel(xOfWalls1 - 10, 3, -zOfWalls1);
	tempTWallModel->Scale(2.0f);
	tWalls.push_back(tempTWallModel);

	for (int i = 0; i < 28; i++) //For loop that automatically renders the entities
	{
		//Function
		wallVec.push_back(tempWallModel = wallMesh->CreateModel(xOfWalls1 - 10, 3, -zOfWalls1 - 5)); //Adding to the vector 
		tempWallModel->Scale(2.0f);
		tempWallModel->SetSkin("conc02.jpg");
		zOfWalls1 += 19.5f; //decrementing the value of x so they spawn with proper distance between them
	}

	//Turn
	tempTWallModel = teeWall->CreateModel(xOfWalls1 - 10, 3, -zOfWalls1);
	tempTWallModel->Scale(2.0f);
	tWalls.push_back(tempTWallModel);

	for (int i = 0; i < 31; i++) //For loop that automatically renders the entities
	{
		//Function
		wallVec.push_back(tempWallModel = wallMesh->CreateModel(xOfWalls1 - 10, 3, -zOfWalls1)); //Adding to the vector 
		tempWallModel->RotateY(90);
		tempWallModel->Scale(2.0f);
		tempWallModel->SetSkin("conc02.jpg");
		xOfWalls1 += 19.5f; //decrementing the value of x so they spawn with proper distance between them
	}

	//Turn
	tempTWallModel = teeWall->CreateModel(xOfWalls1 - 10, 3, -zOfWalls1);
	tempTWallModel->Scale(2.0f);
	tWalls.push_back(tempTWallModel);

	for (int i = 0; i < 27; i++) //For loop that automatically renders the entities
	{
		//Function
		wallVec.push_back(tempWallModel = wallMesh->CreateModel(xOfWalls1 - 10, 3, -zOfWalls1 - 5)); //Adding to the vector 
		tempWallModel->Scale(2.0f);
		tempWallModel->SetSkin("conc02.jpg");
		zOfWalls1 += 19.5f; //decrementing the value of x so they spawn with proper distance between them
	}

	//Turn
	tempTWallModel = teeWall->CreateModel(xOfWalls1 - 10, 3, -zOfWalls1);
	tempTWallModel->Scale(2.0f);
	tWalls.push_back(tempTWallModel);

	for (int i = 0; i < 19; i++) //For loop that automatically renders the entities
	{
		//Function
		wallVec.push_back(tempWallModel = wallMesh->CreateModel(xOfWalls1 - 10, 3, -zOfWalls1)); //Adding to the vector 
		tempWallModel->RotateY(90);
		tempWallModel->Scale(2.0f);
		tempWallModel->SetSkin("conc02.jpg");
		xOfWalls1 += 19.5f; //decrementing the value of x so they spawn with proper distance between them
	}

	//Turn
	tempTWallModel = teeWall->CreateModel(xOfWalls1 - 17, 3, -zOfWalls1);
	tempTWallModel->Scale(2.0f);
	tWalls.push_back(tempTWallModel);


	wallVec.push_back(tempWallModel = wallMesh->CreateModel(xOfWalls1 - 19.5, 3, -zOfWalls1 + 19.5f)); //Adding to the vector 
	tempWallModel->Scale(2.0f);
	tempWallModel->SetSkin("conc02.jpg");
#pragma endregion

#pragma region Outer walls

	//Turn
	tempTWallModel = teeWall->CreateModel(760, 3, -750);
	tempTWallModel->Scale(2.0f);
	tWalls.push_back(tempTWallModel);

	for (int i = 0; i < 71; i++)
	{
		//Function
		wallVec.push_back(tempWallModel = wallMesh->CreateModel(xOfWalls2, 3, -zOfWalls2)); //Adding to the vector 
		tempWallModel->Scale(2.0f);
		tempWallModel->SetSkin("conc02.jpg");
		zOfWalls2 -= 19.5f; //decrementing the value of x so they spawn with proper distance between them
	}

	//Turn
	zOfWalls2 += 10;
	tempTWallModel = teeWall->CreateModel(xOfWalls2, 3, -zOfWalls2);
	tempTWallModel->Scale(2.0f);
	tempTWallModel->RotateY(180);
	tWalls.push_back(tempTWallModel);

	for (int i = 0; i < 62; i++) //For loop that automatically renders the entities
	{
		//Function
		wallVec.push_back(tempWallModel = wallMesh->CreateModel(xOfWalls2 - 5, 3, -zOfWalls2)); //Adding to the vector 
		tempWallModel->RotateY(90);
		tempWallModel->Scale(2.0f);
		tempWallModel->SetSkin("conc02.jpg");
		xOfWalls2 -= 19.5f; //decrementing the value of x so they spawn with proper distance between them
	}

	//Turn
	xOfWalls2 += 7;
	tempTWallModel = teeWall->CreateModel(xOfWalls2, 3, -zOfWalls2);
	tempTWallModel->Scale(2.0f);
	tWalls.push_back(tempTWallModel);

	for (int i = 0; i < 45; i++)
	{
		//Function
		wallVec.push_back(tempWallModel = wallMesh->CreateModel(xOfWalls2, 3, -zOfWalls2)); //Adding to the vector 
		tempWallModel->Scale(2.0f);
		tempWallModel->SetSkin("conc02.jpg");
		zOfWalls2 += 19.5f; //decrementing the value of x so they spawn with proper distance between them
	}

	//Turn
	zOfWalls2 -= 13;
	tempTWallModel = teeWall->CreateModel(xOfWalls2, 3, -zOfWalls2);
	tempTWallModel->Scale(2.0f);
	tWalls.push_back(tempTWallModel);

	for (int i = 0; i < 31; i++) //For loop that automatically renders the entities
	{
		//Function
		wallVec.push_back(tempWallModel = wallMesh->CreateModel(xOfWalls2, 3, -zOfWalls2)); //Adding to the vector 
		tempWallModel->RotateY(90);
		tempWallModel->Scale(2.0f);
		tempWallModel->SetSkin("conc02.jpg");
		xOfWalls2 += 19.5f; //decrementing the value of x so they spawn with proper distance between them
	}

	//Turn
	tempTWallModel = teeWall->CreateModel(xOfWalls2, 3, -zOfWalls2);
	tempTWallModel->Scale(2.0f);
	tWalls.push_back(tempTWallModel);

	for (int i = 0; i < 27; i++)
	{
		//Function
		wallVec.push_back(tempWallModel = wallMesh->CreateModel(xOfWalls2, 3, -zOfWalls2)); //Adding to the vector 
		tempWallModel->Scale(2.0f);
		tempWallModel->SetSkin("conc02.jpg");
		zOfWalls2 += 19.5f; //decrementing the value of x so they spawn with proper distance between them
	}

	//Turn
	tempTWallModel = teeWall->CreateModel(xOfWalls2, 3, -zOfWalls2);
	tempTWallModel->Scale(2.0f);
	tempTWallModel->RotateY(180);
	tWalls.push_back(tempTWallModel);

	for (int i = 0; i < 31; i++) //For loop that automatically renders the entities
	{
		//Function
		wallVec.push_back(tempWallModel = wallMesh->CreateModel(xOfWalls2, 3, -zOfWalls2)); //Adding to the vector 
		tempWallModel->RotateY(90);
		tempWallModel->Scale(2.0f);
		tempWallModel->SetSkin("conc02.jpg");
		xOfWalls2 += 19.5f; //decrementing the value of x so they spawn with proper distance between them
	}



#pragma endregion

}

void spawnStreets(IMesh* street, vector<IModel*> streetVec)
{
	float zOfStreets = -500.0f; //Initial z position of the street(s)
	float xOfStreets = 520.0f; //Initial x position of the street(s)
	IModel* tempStreetModel; //Temporary model

							 /* First line of streets - Where the cars spawn */
	for (int i = 0; i < 6; i++) //For loop that automatically renders the entities
	{
		//Function
		streetVec.push_back(tempStreetModel = street->CreateModel(700, 0, zOfStreets)); //Adding to the vector 
		tempStreetModel->SetSkin("Street_2.jpg"); //Adding the custom skin i created
		tempStreetModel->Scale(40); //Scaling up the streets to look more realistic
		zOfStreets += 175.0f; //Incrementing so the streets look connected
	}

	//Turn
	streetVec.push_back(tempStreetModel = street->CreateModel(700, 0, zOfStreets));
	tempStreetModel->SetSkin("street_turn4.jpg"); //Adding the custom skin i created - Turn
	tempStreetModel->Scale(40);

	//Second line - Along the X axis
	for (int i = 0; i < 4; i++) //For loop that automatically renders the entities
	{
		//Function
		streetVec.push_back(tempStreetModel = street->CreateModel(xOfStreets, -1, 550)); //Adding to the vector 
		tempStreetModel->SetSkin("Street_2.jpg"); //Adding the custom skin i created
		tempStreetModel->Scale(55); //Scaling up the streets to look more realistic
		tempStreetModel->RotateY(90); //Rotating 90 degrees
		xOfStreets -= 240.0f; //Incrementing so the streets look connected
	}

	//Turn
	streetVec.push_back(tempStreetModel = street->CreateModel(xOfStreets + 55, 0, zOfStreets));
	tempStreetModel->SetSkin("street_turn4rightdown.jpg"); //Adding the custom skin i created - Turn
	tempStreetModel->Scale(40);

	//Third line - Along the Z Axis
	for (int i = 0; i < 3; i++) //For loop that automatically renders the entities
	{
		zOfStreets -= 175.0f; //decrementing so the streets look connected
		streetVec.push_back(tempStreetModel = street->CreateModel(xOfStreets + 55, 0, zOfStreets)); //Adding to the vector 
		tempStreetModel->SetSkin("Street_2.jpg"); //Adding the custom skin i created
		tempStreetModel->Scale(40); //Scaling up the streets to look more realistic
	}

	//Turn
	zOfStreets -= 175.0f; //decrementing so the streets look connected
	streetVec.push_back(tempStreetModel = street->CreateModel(xOfStreets + 55, 0, zOfStreets));
	tempStreetModel->SetSkin("street_turn3.jpg"); //Adding the custom skin i created - Turn
	tempStreetModel->Scale(40);

	//Fourth line - Along the X axis
	for (int i = 0; i < 2; i++) //For loop that automatically renders the entities
	{
		//Function
		streetVec.push_back(tempStreetModel = street->CreateModel(xOfStreets + 235, -1, zOfStreets)); //Adding to the vector 
		tempStreetModel->SetSkin("Street_2.jpg"); //Adding the custom skin i created
		tempStreetModel->Scale(55); //Scaling up the streets to look more realistic
		tempStreetModel->RotateY(90); //Rotating 90 degrees
		xOfStreets += 240.0f; //Incrementing so the streets look connected
	}

	//Turn
	xOfStreets += 180.0f; //Incrementing so the streets look connected
	streetVec.push_back(tempStreetModel = street->CreateModel(xOfStreets, 0, zOfStreets));
	tempStreetModel->SetSkin("street_turn2.jpg"); //Adding the custom skin i created - Turn
	tempStreetModel->Scale(40);

	//Fifth line - Along the Z Axis
	for (int i = 0; i < 2; i++) //For loop that automatically renders the entities
	{
		zOfStreets -= 175.0f; //decrementing so the streets look connected
		streetVec.push_back(tempStreetModel = street->CreateModel(xOfStreets, 0, zOfStreets)); //Adding to the vector 
		tempStreetModel->SetSkin("Street_2.jpg"); //Adding the custom skin i created
		tempStreetModel->Scale(40); //Scaling up the streets to look more realistic
	}

	//Turn
	zOfStreets -= 175.0f; //decrementing so the streets look connected
	streetVec.push_back(tempStreetModel = street->CreateModel(xOfStreets, 0, zOfStreets));
	tempStreetModel->SetSkin("street_turn3.jpg"); //Adding the custom skin i created - Turn
	tempStreetModel->Scale(40);

	//Turn
	streetVec.push_back(tempStreetModel = street->CreateModel(700, 0, zOfStreets));
	tempStreetModel->SetSkin("street_turn4leftup.jpg"); //Adding the custom skin i created - Turn
	tempStreetModel->Scale(40);

	//6th line
	streetVec.push_back(tempStreetModel = street->CreateModel(xOfStreets + 235, -1, zOfStreets)); //Adding to the vector 
	tempStreetModel->SetSkin("Street_2.jpg"); //Adding the custom skin i created
	tempStreetModel->Scale(55); //Scaling up the streets to look more realistic
	tempStreetModel->RotateY(90); //Rotating 90 degrees
	xOfStreets += 240.0f; //Incrementing so the streets look connected


}

void spawnCheckpoints(IMesh* checkPmesh, vector<CheckPoints> checkpoints)
{
	CheckPoints temp; //Temporary model

					  //First checkpoint
	temp.checkPointModel = checkPmesh->CreateModel(700, 0, -250); //Function
	temp.checkPointModel->Scale(3);
	temp.state = Unpassed; //Assigning state
	checkpoints.push_back(temp); //Adding to the vector

								 //Second checkpoint
	temp.checkPointModel = checkPmesh->CreateModel(400, 0, 550); //Function
	temp.checkPointModel->Scale(3);
	temp.checkPointModel->RotateY(90);
	temp.state = Unpassed; //Assigning state
	checkpoints.push_back(temp); //Adding to the vector

								 //Third checkpoint
	temp.checkPointModel = checkPmesh->CreateModel(-400, 0, 300); //Function
	temp.checkPointModel->Scale(3);
	temp.state = Unpassed; //Assigning state
	checkpoints.push_back(temp); //Adding to the vector

								 //Fourth checkpoint
	temp.checkPointModel = checkPmesh->CreateModel(-100, 0, -150); //Function
	temp.checkPointModel->Scale(3);
	temp.checkPointModel->RotateY(90);
	temp.state = Unpassed; //Assigning state
	checkpoints.push_back(temp); //Adding to the vector

								 //Fifth checkpoint
	temp.checkPointModel = checkPmesh->CreateModel(220, 0, -410); //Function
	temp.checkPointModel->Scale(3);
	temp.state = Unpassed; //Assigning state
	checkpoints.push_back(temp); //Adding to the vector

								 //Sixth checkpoint
	temp.checkPointModel = checkPmesh->CreateModel(430, 0, -675); //Function
	temp.checkPointModel->RotateY(90);
	temp.checkPointModel->Scale(3);
	temp.state = Unpassed; //Assigning state
	checkpoints.push_back(temp); //Adding to the vector

}

void spawnSkyscrapers(IMesh* skyscrapers, vector<IModel*> sc)
{
	IModel* temp;

	temp = skyscrapers->CreateModel(475, 0, -250); //Function
	temp->SetSkin("skyscraper09.jpg");
	temp->Scale(2.5);
	sc.push_back(temp); //Adding to the vector

	temp = skyscrapers->CreateModel(450, 0, 0); //Function
	temp->SetSkin("skyscraper13.jpg");
	temp->Scale(2.5);
	sc.push_back(temp); //Adding to the vector

	temp = skyscrapers->CreateModel(200, 0, 250); //Function
	temp->SetSkin("skyscraper04.jpg");
	temp->Scale(2.5);
	sc.push_back(temp); //Adding to the vector

	temp = skyscrapers->CreateModel(-100, 0, 150); //Function
	temp->SetSkin("skyscraper02.jpg");
	temp->Scale(2.5);
	sc.push_back(temp); //Adding to the vector

	temp = skyscrapers->CreateModel(-180, 0, -520); //Function
	temp->SetSkin("skyscraper09.jpg");
	temp->Scale(2.5);
	sc.push_back(temp); //Adding to the vector

}

void spawnTribuneNarrowWalls(IMesh* tribuneMesh, vector<IModel*> tribuneWalls)
{
	IModel* temp;
	int zOfTribune = -630;
	int xOfTribune = 300;

	for (int i = 0; i < 2; i++)
	{
		temp = tribuneMesh->CreateModel(590, -45, zOfTribune); //Function
		temp->SetSkin("stone2.jpg");
		temp->Scale(2.5);
		tribuneWalls.push_back(temp); //Adding to the vector
		zOfTribune -= 100;
	}
	zOfTribune += 100;
	for (int i = 0; i < 2; i++)
	{
		temp = tribuneMesh->CreateModel(xOfTribune, -45, zOfTribune); //Function
		temp->SetSkin("stone2.jpg");
		temp->Scale(2.5);
		tribuneWalls.push_back(temp); //Adding to the vector
		zOfTribune += 100;
	}

}

#pragma endregion

void main()
{
	/*Loading in the engine & tracing media file */

	//engine
	I3DEngine* myEngine = New3DEngine(kTLX);
	myEngine->StartWindowed();

	//tracing media folder for the textures
	myEngine->AddMediaFolder("./media");

	/*== Scene setup ==*/
#pragma region Floor, skybox & camera

	//Floor
	IMesh* groundMesh = myEngine->LoadMesh("ground.x");
	IModel* ground = groundMesh->CreateModel(0, 0, 0);
	ground->SetSkin("Baize.jpg"); //The grass texture looks terrible, so i used this texture lol

								  //Skybox
	IMesh* skyBoxMesh = myEngine->LoadMesh("Skybox.x");
	IModel* skyBoxModel = skyBoxMesh->CreateModel(0, -800, 0);

	//Camera
	ICamera* camera;
	camera = myEngine->CreateCamera(kManual); //kManual camera to manually control the camera

#pragma endregion

#pragma region Game Objects (Hovercar, checkpoints etc)
											  //Hovercar
	IMesh* carMesh = myEngine->LoadMesh("race2.x");
	CAR humanCar; //Declaring the car that's controlled by the human
	humanCar.setCool(); //Changing the state of the car
	humanCar.health = 100; //Setting the health, as required

	CAR robotCar1; //Declaring the first robot car
	CAR robotCar2; //Delcaring the second robot car

				   //Changing controller state
	robotCar1.controlledByComputer();
	robotCar2.controlledByComputer();

	robotCar1.health = 100; //Setting health to 100
	robotCar2.health = 100; //Setting health to 100

							//Giant cool starwars looking ship
	IMesh* interstellarShipMesh = myEngine->LoadMesh("Interstellar.x");
	IModel* interstellarModel;

	//Checkpoints
	IMesh* checkpointMesh = myEngine->LoadMesh("Checkpoint.x");
	vector<CheckPoints> checkpoint;

	//Isles
	IMesh* isleMesh = myEngine->LoadMesh("IsleStraight.x");
	IMesh* teeWalls = myEngine->LoadMesh("IsleTee.x");
	vector<IModel*> isleVector;
	vector<IModel*> tWalls;

	//Walls
	IMesh* wallMesh = myEngine->LoadMesh("Wall.x");
	vector<IModel*> wallVector;

	//Dummy
	IMesh* dummyMesh = myEngine->LoadMesh("Dummy.x");
	DUMMIES dummyFirstPerson;
	DUMMIES dummyThirdPerson;
	DUMMIES dummySurveillance;

	///Setting the status of the dummies to attached/unattached so they dont collide/collide with the scene
	dummyFirstPerson.setAttached();
	dummyThirdPerson.setAttached();
	dummySurveillance.setAttached();

	///Checkpoint dummies
	DUMMIES checkpDummy1;
	DUMMIES checkpDummy2;
	DUMMIES checkpDummy3;
	DUMMIES checkpDummy4;
	DUMMIES checkpDummy5;
	DUMMIES checkpDummy6;

	///Setting the status of the dummies to attached/unattached so they dont collide/collide with the scene
	checkpDummy1.setNotAttached();
	checkpDummy2.setNotAttached();
	checkpDummy3.setNotAttached();
	checkpDummy4.setNotAttached();
	checkpDummy5.setNotAttached();
	checkpDummy6.setNotAttached();

	DUMMIES collisionDummy1;
	DUMMIES collisionDummy2;
	DUMMIES collisionDummy3;
	DUMMIES collisionDummy4;
	DUMMIES collisionDummy5;
	DUMMIES collisionDummy6;
	DUMMIES collisionDummy7;
	DUMMIES collisionDummy8;


	//Streets
	IMesh* streetMesh = myEngine->LoadMesh("Walkway.x");
	vector<IModel*> streetVec;

	//Cross
	IMesh* crossMesh = myEngine->LoadMesh("Cross.x");
	vector<IModel*> cross;

	//Sky scrapers
	IMesh* skyScraper = myEngine->LoadMesh("skyscraper09.x");
	vector<IModel*> skyscrapersVec;

	//Water tank
	IMesh* waterTankMesh = myEngine->LoadMesh("TankLarge2.x");
	IMesh* waterTankMesh2 = myEngine->LoadMesh("TankLarge1.x");
	IModel* waterTankModel;
	IModel* waterTankModel2;

	//Tribune
	IMesh* tribuneMesh = myEngine->LoadMesh("Tribune1.x");
	IModel* tribune;
	vector<IModel*> tribuneNarrowWalls;

	//Tree
	IMesh* tree = myEngine->LoadMesh("Tree1.x");
	IModel* treeModel;

#pragma endregion

#pragma region Map design

	/*====== Cars ======*/
	humanCar.carModel = carMesh->CreateModel(700, 2, -500);
	robotCar1.carModel = carMesh->CreateModel(685, 2, -500);
	robotCar2.carModel = carMesh->CreateModel(715, 2, -500);

	humanCar.carModel->Scale(2);
	robotCar1.carModel->Scale(2);
	robotCar2.carModel->Scale(2);

	humanCar.carModel->SetSkin("ff06.jpg");
	///Since the dummy is a part of the car
	dummyFirstPerson.dummyModel = dummyMesh->CreateModel(0, 4, -13);
	dummyFirstPerson.dummyModel->AttachToParent(humanCar.carModel);

	dummyThirdPerson.dummyModel = dummyMesh->CreateModel(0, 10, -20);
	dummyThirdPerson.dummyModel->AttachToParent(humanCar.carModel);



	/*====== Track (Walls, checkpoints) ======*/
	///Checkpoints
	spawnCheckpoints(checkpointMesh, checkpoint);

	///Dummies for the checkpoints so the cross can be displayed when passed:
	checkpDummy1.dummyModel = dummyMesh->CreateModel(700, 10, -250);
	checkpDummy2.dummyModel = dummyMesh->CreateModel(400, 10, 550);
	checkpDummy3.dummyModel = dummyMesh->CreateModel(-400, 10, 300);
	checkpDummy4.dummyModel = dummyMesh->CreateModel(-100, 10, -150);
	checkpDummy5.dummyModel = dummyMesh->CreateModel(220, 10, -410);
	checkpDummy6.dummyModel = dummyMesh->CreateModel(430, 10, -675);

	///Street
	spawnStreets(streetMesh, streetVec);

	///Walls & TeeWalls
	spawnWalls(wallMesh, wallVector, teeWalls, tWalls);



	/*====== Obstacles ======*/
	///Tribune
	tribune = tribuneMesh->CreateModel(700, 0, 10);
	collisionDummy1.dummyModel = dummyMesh->CreateModel(700, 3, 10);
	tribune->SetSkin("stone2.jpg");
	spawnTribuneNarrowWalls(tribuneMesh, tribuneNarrowWalls);
	collisionDummy5.dummyModel = dummyMesh->CreateModel(590, 5, -630);
	collisionDummy6.dummyModel = dummyMesh->CreateModel(590, 5, -730);
	collisionDummy7.dummyModel = dummyMesh->CreateModel(300, 5, -630);
	collisionDummy8.dummyModel = dummyMesh->CreateModel(590, 5, -730);

	///Water tank
	waterTankModel = waterTankMesh->CreateModel(600, 0, 540);
	collisionDummy2.dummyModel = dummyMesh->CreateModel(600, 3, 540);
	waterTankModel2 = waterTankMesh->CreateModel(-385, 0, 10);
	collisionDummy3.dummyModel = dummyMesh->CreateModel(-385, 3, 10);

	///Tree
	treeModel = tree->CreateModel(50, 0, 550);
	collisionDummy4.dummyModel = dummyMesh->CreateModel(50, 3, 550);
	treeModel->Scale(15);



	/*====== Decoration ======*/

	//Interstellar ship
	interstellarModel = interstellarShipMesh->CreateModel(700, 500, -500);
	dummySurveillance.dummyModel = dummyMesh->CreateModel(0, -20, 0);
	interstellarModel->Scale(3.0f);
	dummySurveillance.dummyModel->AttachToParent(interstellarModel);

	//Skyscrapers
	spawnSkyscrapers(skyScraper, skyscrapersVec);

#pragma endregion

#pragma region Camera modes

	CAMERA_STATE stateOfCamera;

	//setting the state of the camera to free moving since thats what the assignment requires
	stateOfCamera.setFreeMoving();

	//Free moving
	float freeMovingCameraMatrix[4][4];
	camera->SetPosition(250, 1000, -650);
	camera->RotateX(65);
	camera->GetMatrix(&freeMovingCameraMatrix[0][0]);
	camera->ResetOrientation();

	//First-Person
	float firstPersonCameraMatrix[4][4];
	camera->SetPosition(0, 2, 15);
	camera->GetMatrix(&firstPersonCameraMatrix[0][0]);
	camera->ResetOrientation();

	//Third-Person
	float thirdPersonCameraMatrix[4][4];
	camera->SetPosition(0, 10, -20);
	camera->RotateX(10);
	camera->GetMatrix(&thirdPersonCameraMatrix[0][0]);
	camera->ResetOrientation();

	//Surveillance
	float surveillanceCameraMatrix[4][4];
	camera->GetMatrix(&surveillanceCameraMatrix[0][0]);
	camera->ResetOrientation();

	//Mouse capture for manual mouse movement - As required by the assignment
	myEngine->StartMouseCapture();
	bool mouseActive = false; //state of mouse capture
	float mouseRotationSpeed = 10.0f; //Speed of mouse rotation
	float cameraMovementSpeed = 50.0f; //Speed of camera movement

									   //Initial position of the camera
	camera->SetPosition(700, 20, -540);
	camera->RotateX(10);

#pragma endregion

#pragma region Movement variables

	/*==========================================================================================================\
	| Acceleration/Decelaration variables that will be used so the car doesn't have a fixed speed -> simulating |
	| realistic physics                                                                                         |
	\==========================================================================================================*/

	//Front <> Back movement
	float velocity = 0.0f; //Velocity of the vehicle(s)
	float maxVelocity = 0.65f; //Maximum velocity so the speed is limited
	float acceleration = 0.1f; //Acceleration of the vehicle
	float deceleration = 0.3f; //Deceleration of the vehicle <> Much slower than the acceleration

	bool moveUp = true; //Switch to move the car up and down
	float moveBack = 10.0f; //Speed of moving back

#pragma endregion

#pragma region Game stages

	string gameStage = "Demo";

	GAME_STAGE stageOfGame;

	stageOfGame.setDemo(); //Initial stage of the game 

#pragma endregion

#pragma region Extras

	IFont* roboticFont = myEngine->LoadFont("Magneto", 25); //Loading in font <> "Magneto" font to look robotic
	IFont* largeRoboticText = myEngine->LoadFont("Magneto", 60); //Larger text
	ISprite* backdrop = myEngine->CreateSprite("Player_UI3.png", -100, 0); //Loading in GUI

																		   //Dug around the source code of the engine and found out you can change the name of the window
	myEngine->SetWindowCaption("Al-Ghalibi Mohammed Assignment 3");

#pragma endregion

#pragma region Timers

	//Initial countdown for when the game starts
	static float initialCountDown = 3.0f;

	//Overheat timers
	static float overheatTimer = 4.0f;
	static float overheatCoolDown = 6.0f;

	//Game time
	static float gameTime = 0.0f;

#pragma endregion

	//Main game loop
	while (myEngine->IsRunning())
	{
		//Drawing the scene
		myEngine->DrawScene();

#pragma region Delta time & Frames per second

		float deltaTime = myEngine->Timer(); //calculating deltaTime
		float fps = 1 / deltaTime; //To calculate the frames of the game
		gameTime += deltaTime; //incrementing game time to display on screen

#pragma endregion

#pragma region Game stages updates

		if (stageOfGame.state == Demo && gameStage == "Demo") //Checking whether the game stage is "demo" or not
		{
			if (myEngine->KeyHit(Key_Space)) //If space is pressed
			{
				stageOfGame.setCountDown();
				gameStage = "Count-Down"; //Update game stage
			}
		}

		if (stageOfGame.state == Count_Down) //Checking whether the game stage is "count down" or not
		{
			initialCountDown -= deltaTime; //Counting down
			if (initialCountDown <= 0.0f) //Update game stage once the timer is over
			{
				stageOfGame.setStage0();
				gameStage = "Stage 0";
			}
		}

#pragma endregion

#pragma region On-screen text

		//Speed
		stringstream velocityText;
		velocityText << round(velocity * 100); //Rounding it up to an integer - as required in the assignment brief
		roboticFont->Draw(velocityText.str(), 280, 25, kBlack); //Drawing the font onto the screen

																//Frames per second
		stringstream framesPerSecond;
		framesPerSecond << round(fps * 1); //Rounding it up to an integer - for better visuals
		roboticFont->Draw(framesPerSecond.str(), 260, 47, kBlack); //Drawing the font onto the screen  

																   //Game stage
		stringstream gameStageText;
		gameStageText << gameStage; //Rounding it up to an integer - for better visuals
		roboticFont->Draw(gameStageText.str(), 1050, 28, kBlack); //Drawing the font onto the screen 

																  //"Start game" text
		if (stageOfGame.state == Demo || gameStage == "Demo")
		{
			largeRoboticText->Draw("Press Space to play!", 650, 240, kBlack, kCentre, kVCentre);
		}

		//Count-Down
		if (stageOfGame.state == Count_Down || gameStage == "Count-Down")
		{
			stringstream countDownText;
			countDownText << round(initialCountDown * 1); //Rounding it up to an integer - for better visuals
			largeRoboticText->Draw(countDownText.str(), 600, 25, kBlack); //Drawing the font onto the screen 
		}

		//Health of human controlled car
		stringstream carHealth;
		carHealth << humanCar.health; //Rounding it up to an integer - for better visuals
		roboticFont->Draw(carHealth.str(), 290, 75, kBlack); //Drawing the font onto the screen 

															 //Game time
		stringstream gameTimeText;
		gameTimeText << round(gameTime); //Rounding it up to an integer - for better visuals
		roboticFont->Draw(gameTimeText.str(), 1050, 82, kBlack); //Drawing the font onto the screen 


#pragma endregion

																 //Checking if the stage of the game is "playable"
		if (stageOfGame.state == Stage_0 ||
			stageOfGame.state == Stage_1 ||
			stageOfGame.state == Stage_2 ||
			stageOfGame.state == Stage_3 ||
			stageOfGame.state == Stage_4 ||
			stageOfGame.state == Stage_5)
		{

#pragma region Car movement

#pragma region Acceleration <> Decelaration 
			//Increasing speed over-time (Accelerating)
			if (myEngine->KeyHeld(Key_W) && velocity < 1.0f)
			{
				velocity += deltaTime * acceleration;
			}

			else if (velocity < -1 && myEngine->KeyHeld(Key_W))
			{
				velocity += deltaTime * acceleration * 2;
			}

			//Decelarting if the player isn't holding the "W" key - Essentially simulating friction
			if (!myEngine->KeyHeld(Key_W) && velocity > 0.0f)
			{
				velocity -= deltaTime * deceleration;
			}

			//Setting a limit to the velocity so it doesn't go below 0 if the player isn't holding "W"
			if (!myEngine->KeyHeld(Key_W) && velocity < 0.0f)
			{
				velocity = 0.0f;
			}

			//Setting a limit to the velocity so it doesn't go overboard
			if (velocity > maxVelocity)
			{
				velocity *= 0.99f;
			}
#pragma endregion

#pragma region Boost & Overheat

			//Temporarily increasing the velocity

			if (myEngine->KeyHeld(Key_Space))
			{
				overheatTimer -= deltaTime;
				velocity += 0.02f;
				if (velocity > maxVelocity)
				{
					velocity *= 0.99f;
				}
			}

#pragma endregion

#pragma region Move back

			if (myEngine->KeyHeld(Key_S))
			{
				humanCar.carModel->MoveLocalZ(-moveBack * deltaTime);
			}

#pragma endregion

#pragma region Rotation

			if (myEngine->KeyHeld(Key_A))
			{
				humanCar.carModel->RotateY(-0.2f);
			}

			if (myEngine->KeyHeld(Key_D))
			{
				humanCar.carModel->RotateY(0.2f);
			}


#pragma endregion

			humanCar.carModel->MoveLocalZ(velocity); //Moving car

#pragma endregion

#pragma region Collision detection

			for (IModel* wall : wallVector)
			{
				collisionDetectionWall(carMesh, wall, humanCar, velocity, stageOfGame);
			}

			passCheckPointCollision(humanCar, checkpDummy1, crossMesh, cross, stageOfGame);
			passCheckPointCollision(humanCar, checkpDummy2, crossMesh, cross, stageOfGame);
			passCheckPointCollision(humanCar, checkpDummy3, crossMesh, cross, stageOfGame);
			passCheckPointCollision(humanCar, checkpDummy4, crossMesh, cross, stageOfGame);
			passCheckPointCollision(humanCar, checkpDummy5, crossMesh, cross, stageOfGame);
			passCheckPointCollision(humanCar, checkpDummy6, crossMesh, cross, stageOfGame);

			collisionDetectionDummy(dummyMesh, collisionDummy1, humanCar, velocity);
			collisionDetectionDummy(dummyMesh, collisionDummy2, humanCar, velocity);
			collisionDetectionDummy(dummyMesh, collisionDummy3, humanCar, velocity);
			collisionDetectionDummy(dummyMesh, collisionDummy4, humanCar, velocity);
			collisionDetectionDummy(dummyMesh, collisionDummy5, humanCar, velocity);
			collisionDetectionDummy(dummyMesh, collisionDummy6, humanCar, velocity);
			collisionDetectionDummy(dummyMesh, collisionDummy7, humanCar, velocity);
			collisionDetectionDummy(dummyMesh, collisionDummy8, humanCar, velocity);




#pragma endregion

		}

		//Hover effect
#pragma region Move up and down

		if (moveUp)
		{
			humanCar.carModel->MoveY(2.0f * deltaTime);
			robotCar1.carModel->MoveY(2.0f * deltaTime);
			robotCar2.carModel->MoveY(2.0f * deltaTime);
			if (humanCar.carModel->GetY() >= 4)
			{
				moveUp = false;
			}
		}
		else
		{
			humanCar.carModel->MoveY(-2.0f * deltaTime);
			robotCar1.carModel->MoveY(-2.0f * deltaTime);
			robotCar2.carModel->MoveY(-2.0f * deltaTime);
			if (humanCar.carModel->GetY() <= 2)
			{
				moveUp = true;
			}
		}

#pragma endregion

#pragma region Camera positioning

		//Free-Moving Camera
		if (myEngine->KeyHit(Key_2))
		{
			stateOfCamera.setFreeMoving();
			camera->SetMatrix(&freeMovingCameraMatrix[0][0]);
			camera->DetachFromParent();
		}

		//First-Person Camera
		if (myEngine->KeyHit(Key_1))
		{
			stateOfCamera.setFirstPerson();
			camera->SetMatrix(&firstPersonCameraMatrix[0][0]);
			camera->AttachToParent(dummyFirstPerson.dummyModel);
		}

		//Third-Person Camera
		if (myEngine->KeyHit(Key_3))
		{
			stateOfCamera.setThirdPerson();
			camera->SetMatrix(&thirdPersonCameraMatrix[0][0]);
			camera->AttachToParent(dummyThirdPerson.dummyModel);
		}

		//Surveillance Camera
		if (myEngine->KeyHit(Key_4))
		{
			stateOfCamera.setSurveillance();
			camera->SetMatrix(&surveillanceCameraMatrix[0][0]);
			camera->AttachToParent(dummySurveillance.dummyModel);
		}

		if (stateOfCamera.state == Surveillance)
		{
			camera->LookAt(humanCar.carModel);
		}

#pragma endregion

#pragma region Camera movement & rotation

		//Forwards
		if (myEngine->KeyHeld(Key_Up))
		{
			camera->MoveLocalZ(cameraMovementSpeed * deltaTime);
		}

		//Backwards
		if (myEngine->KeyHeld(Key_Down))
		{
			camera->MoveLocalZ(-cameraMovementSpeed * deltaTime);
		}

		//Left
		if (myEngine->KeyHeld(Key_Left))
		{
			camera->MoveLocalX(-cameraMovementSpeed * deltaTime);
		}

		//Right
		if (myEngine->KeyHeld(Key_Right))
		{
			camera->MoveLocalX(cameraMovementSpeed * deltaTime);
		}

		//Reset orientation
		if (myEngine->KeyHit(Key_C))
		{
			camera->ResetOrientation(); //Dug in the source code to find this function
		}

		/*===========================================================================================================\
		| I made it so the movement of the mouse is 1. Incredibly smooth and satisfying and 2. Optional, the user can|
		| now choose whether they want to control the mouse movement or not because i noticed that when testing      |
		|  and reviewing the code whilst the game is running, my mouse was running and the game was going crazy even |
		| if i wasn't really in the game or playing it. So i added this feature because it pissed me off haha        |
		\===========================================================================================================*/

		//Enable the mouse capturing function to not move it at all times
		if (myEngine->KeyHit(Key_Return)) //That's "Enter" btw, both on numpad and main keyboard
		{
			if (mouseActive == true)
			{
				myEngine->StopMouseCapture();
				mouseActive = false;
			}

			else
			{
				myEngine->StartMouseCapture();
				mouseActive = true;
			}
		}

		//And btw, both rotations are using deltaTime, as required by the assignment
		if (mouseActive == true)
		{
			//Rotate in the "X" axis
			int mouseMoveX = myEngine->GetMouseMovementX();
			camera->RotateY(mouseMoveX * mouseRotationSpeed * deltaTime);

			//Rotate in the "Y" axis
			int mouseMoveY = myEngine->GetMouseMovementY();
			camera->RotateLocalX(mouseMoveY * mouseRotationSpeed * deltaTime);
		}

#pragma endregion

		//Extra features
#pragma region Extras

		/*===========================================================================================================\
		| Move the starwars looking ship around in a circle, essentially acting as a "drone", which is also connected|
		| To the "Surveillance" cameara, thought it'd be a cool idea since the ship is supposed to be an "enemy" so  |
		| why not make it track your movement? to prepare for something evil perhaps? Who knows ;)                   |
		\===========================================================================================================*/

		interstellarModel->MoveLocalZ(3.0f * deltaTime);
		interstellarModel->RotateY(-3.0f * deltaTime);

#pragma endregion

#pragma region Closing the game

		//Close game by hitting the esc key
		if (myEngine->KeyHit(Key_Escape))
		{
			myEngine->Stop();
		}

#pragma endregion

		//updating the scene each frame
		for (int delay = 0; delay < 1000000; delay++) {}
	}
	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
