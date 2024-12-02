from sqlalchemy.orm import Session
from app.models.monitor import MonitorRecord

from sqlalchemy.orm import Session
from app.models.monitor import MonitorRecord
from app.schemas.monitor import MonitorCreate

class MonitorService:
    @staticmethod
    def create_monitor_record(db: Session, record: MonitorCreate):
        """Guarda un nuevo registro de monitorización en la base de datos."""
        db_record = MonitorRecord(**record.dict())
        db.add(db_record)
        db.commit()
        db.refresh(db_record)
        return db_record

    @staticmethod
    def get_all_monitor_records(db: Session):
        """Obtiene todos los registros de monitorización."""
        return db.query(MonitorRecord).all()

