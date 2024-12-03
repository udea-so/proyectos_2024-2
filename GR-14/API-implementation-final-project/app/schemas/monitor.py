from pydantic import BaseModel
from datetime import datetime

class MonitorCreate(BaseModel):
    cpu_usage: float
    memory_usage: float

class MonitorResponse(MonitorCreate):
    id: int
    timestamp: datetime

    class Config:
        from_attributes = True
