from pydantic import BaseModel
from datetime import datetime

class ProfileCreate(BaseModel):
    function_name: str
    module_name: str

class ProfileResponse(ProfileCreate):
    id: int
    parameters: str
    result: str
    timestamp: datetime

    class Config:
        from_attributes = True
