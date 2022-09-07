// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveEquation.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/Vector.h"
#include "Chaos/Vector.h"
#include "CoreFwd.h"

// Sets default values
AWaveEquation::AWaveEquation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWaveEquation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaveEquation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWaveEquation::reset()
{

    auto gauss = [](float x, float sigma)
    {
        double tow_pi = 6.2831853071795864769;
        return 1.0f / UKismetMathLibrary::Sqrt(tow_pi) * sigma * exp(-x * x / (2.0f * sigma * sigma));
    };

    int cx1 = kWaveGrid / 3;
    int cy1 = kWaveGrid / 3;
    int cx2 = kWaveGrid * 2 / 3;
    int cy2 = kWaveGrid * 2 / 3;
    for (int x = 1; x < kWaveGrid - 1; ++x)
    {
        for (int y = 1; y < kWaveGrid - 1; ++y)
        {
            int index = this->valueIndex(x, y);
            float value = 0.0f;

            {
                FVector xy(x, y, 0);
                FVector cxy(cx1, cy1, 0);
                float norm = FVector::Distance(xy, cxy);
                value += gauss(norm, 3.0f) * 20.0f;
            }
            {
                FVector xy(x, y, 0);
                FVector cxy(cx2, cy2, 0);
                float norm = FVector::Distance(xy, cxy);
                value += gauss(norm, 3.0f) * 20.0f;
            }

            _u_cur[index] = value;
        }
    }

    _u_pre = _u_new = _u_cur;
}
void AWaveEquation::step()
{
    float deltaX = float(kWaveWidth) / float(kWaveGrid);
    float deltaT = 1.0f / 60.0f;
    float c = 2.0f;
    float mul = deltaT * deltaT * c * c / (deltaX * deltaX);
    for (int x = 1; x < kWaveGrid - 1; ++x)
    {
        for (int y = 1; y < kWaveGrid - 1; ++y)
        {
            int index = this->valueIndex(x, y);

            float uL = _u_cur[this->valueIndex(x - 1, y)];
            float uR = _u_cur[this->valueIndex(x + 1, y)];
            float uT = _u_cur[this->valueIndex(x, y - 1)];
            float uB = _u_cur[this->valueIndex(x, y + 1)];

            float u_pre = _u_pre[index];
            float u = _u_cur[index];
            _u_new[index] = u + u - u_pre + mul * (-4.0f * u + uL + uR + uT + uB);
        }
    }

    std::swap(_u_pre, _u_cur);
    std::swap(_u_cur, _u_new);
}

