from sqlalchemy import Column, Integer, String, Text, DateTime
from app.core.database import Base
from datetime import datetime

class ProfileRecord(Base):
    __tablename__ = "profile_records"

    id = Column(Integer, primary_key=True, index=True)
    function_name = Column(String, nullable=False)
    module_name = Column(String, nullable=False)
    profile_data = Column(Text, nullable=False)
    timestamp = Column(DateTime, default=datetime.utcnow)
