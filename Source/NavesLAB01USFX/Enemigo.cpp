#include "Enemigo.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AEnemigo::AEnemigo()
{
	PrimaryActorTick.bCanEverTick = true;

	MallaEnemigo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaEnemigo"));
	RootComponent = MallaEnemigo;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Torus.Shape_Torus'"));

	if (MallaAsset.Succeeded())
	{
		MallaEnemigo->SetStaticMesh(MallaAsset.Object);
	}
}

void AEnemigo::BeginPlay()
{
	Super::BeginPlay();

	// Guardar posición inicial
	PosicionInicial = GetActorLocation();

	// Desfase para que no todos hagan el zig-zag igual
	TiempoSerpiente = PosicionInicial.Y * 0.01f;
}

void AEnemigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector PosicionActual = GetActorLocation();

	// avanzar el tiempo
	TiempoSerpiente += DeltaTime;

	// movimiento hacia el jugador (descender)
	PosicionActual.X -= VelocidadMovimiento * DeltaTime;

	// zig-zag lateral
	PosicionActual.Y = PosicionInicial.Y +
		FMath::Sin(TiempoSerpiente * FrecuenciaSerpiente) * AmplitudSerpiente;

	SetActorLocation(PosicionActual);
}