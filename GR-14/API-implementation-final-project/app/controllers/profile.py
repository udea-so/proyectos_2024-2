import cProfile
import io
import pstats
from fastapi import APIRouter, Depends
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
    """Detiene el perfilado y guarda los resultados en la base de datos."""
    global profiler
    profiler.disable()
    s = io.StringIO()
    ps = pstats.Stats(profiler, stream=s).sort_stats("cumulative")
    ps.print_stats()
    profile_data = s.getvalue()
    return ProfileService.create_profile_record(db, record, profile_data)

@router.get("/", response_model=list[ProfileResponse])
def get_profile_data(db: Session = Depends(get_db)):
    """Obtiene todos los registros de perfilado."""
    return ProfileService.get_all_profile_records(db)
