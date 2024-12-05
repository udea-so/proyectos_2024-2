import cProfile
import io
import pstats
from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy.orm import Session
from app.schemas.profile import ProfileCreate, ProfileResponse
from app.services.profile import ProfileService
from app.core.database import get_db

router = APIRouter()

profiler = None

@router.post("/start", response_model=str)
def start_profiling():
    """Inicia el perfilado de funciones."""
    global profiler
    profiler = cProfile.Profile()
    profiler.enable()
    return "Perfilado iniciado."

@router.post("/stop", response_model=ProfileResponse)
def stop_profiling(record: ProfileCreate, db: Session = Depends(get_db)):
    """Detiene el perfilado, filtra resultados relevantes y guarda en la base de datos."""
    global profiler
    if not profiler:
        raise HTTPException(status_code=400, detail="El perfilado no ha sido iniciado.")

    # Detener el perfilador
    profiler.disable()

    # Capturar estadísticas
    s = io.StringIO()
    ps = pstats.Stats(profiler, stream=s).sort_stats("cumulative")
    ps.print_stats()

    # Filtrar estadísticas específicas de la función
    filtered_stats = io.StringIO()
    ps = pstats.Stats(profiler, stream=filtered_stats).sort_stats("cumulative")
    ps.print_stats(lambda x: record.function_name in x)

    # Guarda solo los datos relevantes
    profile_data = filtered_stats.getvalue()

    # Guardar en la base de datos
    return ProfileService.create_profile_record(
        db,
        record,
        parameters="{}",
        result=profile_data
    )

@router.get("/", response_model=list[ProfileResponse])
def get_profile_data(db: Session = Depends(get_db)):
    """Obtiene todos los registros de perfilado."""
    return ProfileService.get_all_profile_records(db)
