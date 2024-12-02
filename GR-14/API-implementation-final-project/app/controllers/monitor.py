from fastapi import APIRouter, Depends
from sqlalchemy.orm import Session
from app.schemas.monitor import MonitorCreate, MonitorResponse
from app.services.monitor import MonitorService
from app.core.database import get_db
import psutil
import time
from threading import Thread

router = APIRouter()
monitoring = False

def collect_metrics(db: Session):
    """Función para recolectar métricas y guardarlas en la base de datos."""
    global monitoring
    while monitoring:
        data = {
            "cpu_usage": psutil.cpu_percent(interval=1),
            "memory_usage": psutil.virtual_memory().percent,
        }
        MonitorService.create_monitor_record(db, MonitorCreate(**data))

@router.post("/start", response_model=str)
def start_monitoring(db: Session = Depends(get_db)):
    """Inicia el monitoreo del sistema."""
    global monitoring
    if not monitoring:
        monitoring = True
        Thread(target=collect_metrics, args=(db,), daemon=True).start()
        return "Monitorización iniciada."
    return "La monitorización ya está en curso."

@router.post("/stop", response_model=str)
def stop_monitoring():
    """Detiene el monitoreo."""
    global monitoring
    monitoring = False
    return "Monitorización detenida."

@router.get("/", response_model=list[MonitorResponse])
def get_monitor_data(db: Session = Depends(get_db)):
    """Obtiene todos los registros de monitorización."""
    return MonitorService.get_all_monitor_records(db)
